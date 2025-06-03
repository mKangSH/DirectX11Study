#include "pch.h"
#include "ModelAnimator.h"
#include "../00.Engine/Resource/Material.h"
#include "../00.Engine/Resource/Model/Model.h"
#include "../00.Engine/Resource/Model/ModelMesh.h"
#include "../00.Engine/Resource/Model/ModelAnimation.h"

ModelAnimator::ModelAnimator(std::shared_ptr<Shader> shader)
	: Super(ComponentType::Animator), _shader(shader)
{

}

ModelAnimator::~ModelAnimator()
{

}

void ModelAnimator::Update()
{
	if (_model == nullptr)
	{
		return;
	}

	if (_texture == nullptr)
	{
		CreateTexture();
	}

	TweenFrameDesc& desc = _tweenFrameDesc;
	desc.current.sumTime += DELTATIME;
	{
		std::shared_ptr<ModelAnimation> currentAnimation = _model->GetAnimationByIndex(desc.current.animationIndex);
		if (currentAnimation)
		{
			float timePerFrame = 1 / (currentAnimation->frameRate * desc.current.speed);
			if (desc.current.sumTime >= timePerFrame)
			{
				desc.current.sumTime = 0.0f;
				desc.current.currentFrame = (desc.current.currentFrame + 1) % currentAnimation->frameCount;
				desc.current.nextFrame = (desc.current.currentFrame + 1) % currentAnimation->frameCount;
			}

			desc.current.ratio = (desc.current.sumTime / timePerFrame);
		}
	}

	if (desc.next.animationIndex >= 0)
	{
		desc.tweenSumTime += DELTATIME;
		desc.tweenRatio = desc.tweenSumTime / desc.tweenDuration;

		if (desc.tweenRatio >= 1.0f)
		{
			desc.current = desc.next;
			desc.ClearNextAnimation();
		}
		else
		{
			std::shared_ptr<ModelAnimation> nextAnimation = _model->GetAnimationByIndex(desc.next.animationIndex);
			desc.next.sumTime += DELTATIME;

			float timePerFrame = 1.0f / (nextAnimation->frameRate * desc.next.speed);
			if (desc.next.ratio >= 1.0f)
			{
				desc.next.sumTime = 0.0f;
				desc.next.currentFrame = (desc.next.currentFrame + 1) % nextAnimation->frameCount;
				desc.next.nextFrame = (desc.next.currentFrame + 1) % nextAnimation->frameCount;
			}

			desc.next.ratio = (desc.next.sumTime / timePerFrame);
		}
	}

	// Animation Update
	ImGui::InputInt("Animation Index", &desc.current.animationIndex);
	_keyframeDesc.animationIndex %= _model->GetAnimationCount();

	static int32 nextAnimationIndex = 0;
	if (ImGui::InputInt("Next Animation Index", &nextAnimationIndex))
	{
		nextAnimationIndex %= _model->GetAnimationCount();
		desc.ClearNextAnimation();
		desc.next.animationIndex = nextAnimationIndex;
	}

	if (_model->GetAnimationCount() > 0)
	{
		desc.current.animationIndex %= _model->GetAnimationCount();
	}

	ImGui::InputFloat("Animation Speed", &desc.current.speed, 0.5f, 4.0f);

	// 애니메이션 현재 프레임 정보
	RENDER->UploadTweenFrameDesc(desc);

	// ShaderResourceView 를 통해 정보 전달
	_shader->GetSRV("TransformMap")->SetResource(_shaderResourceView.Get());

	// Bones
	BoneDesc boneDesc;

	const uint32 boneCount = _model->GetBoneCount();
	for (uint32 i = 0; i < boneCount; i++)
	{
		std::shared_ptr<ModelBone> bone = _model->GetBoneByIndex(i);
		boneDesc.transforms[i] = bone->transform;
	}
	RENDER->UploadBoneDesc(boneDesc);

	Matrix world = GetTransform()->GetWorldMatrix();
	RENDER->UploadTransformDesc(TransformDesc{ world });

	const auto& meshes = _model->GetMeshes();
	for (auto& mesh : meshes)
	{
		if (mesh->material)
		{
			mesh->material->Update();
		}

		// BoneIndex
		_shader->GetScalar("BoneIndex")->SetInt(mesh->boneIndex);

		uint32 stride = mesh->vertexBuffer->GetStride();
		uint32 offset = mesh->vertexBuffer->GetOffset();

		DEVICECONTEXT->IASetVertexBuffers(0, 1, mesh->vertexBuffer->GetBuffer().GetAddressOf(), &stride, &offset);
		DEVICECONTEXT->IASetIndexBuffer(mesh->indexBuffer->GetBuffer().Get(), DXGI_FORMAT_R32_UINT, 0);

		RasterizerType rasterizerType = RENDER->GetRasterizerState();
		_shader->DrawIndexed(0, static_cast<UINT>(rasterizerType), mesh->indexBuffer->GetCount(), 0, 0);
	}
}

void ModelAnimator::SetModel(std::shared_ptr<Model> model)
{
	_model = model;

	const auto& materials = _model->GetMaterials();
	for (auto& material : materials)
	{
		material->SetShader(_shader);
	}
}

void ModelAnimator::CreateTexture()
{
	if (_model->GetAnimationCount() == 0)
	{
		return;
	}

	_animationTransforms.resize(_model->GetAnimationCount());
	for (uint32 i = 0; i < _model->GetAnimationCount(); i++)
	{
		CreateAniamtionTransform(i);
	}

	// CreateTexture
	{
		D3D11_TEXTURE2D_DESC desc = {};
		ZeroMemory(&desc, sizeof(desc));
		desc.Width = MAX_MODEL_TRANSFORMS * 4;
		desc.Height = MAX_MODEL_KEYFRAMES;
		desc.ArraySize = _model->GetAnimationCount();
		desc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		desc.Usage = D3D11_USAGE_IMMUTABLE;
		desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		desc.MipLevels = 1;
		desc.SampleDesc.Count = 1;

		const uint32 dataSize = MAX_MODEL_TRANSFORMS * sizeof(Matrix);
		const uint32 pageSize = dataSize * MAX_MODEL_KEYFRAMES;
		void* mallocPtr = ::malloc(pageSize * _model->GetAnimationCount());

		for (uint32 c = 0; c < _model->GetAnimationCount(); c++)
		{
			uint32 startOffset = c * pageSize;
			BYTE* pageStartPtr = reinterpret_cast<BYTE*>(mallocPtr) + startOffset;

			for (uint32 f = 0; f < MAX_MODEL_KEYFRAMES; f++)
			{
				void* ptr = pageStartPtr + dataSize * f;
				::memcpy(ptr, _animationTransforms[c].transforms[f].data(), dataSize);
			}
		}

		std::vector<D3D11_SUBRESOURCE_DATA> subResources(_model->GetAnimationCount());

		for (uint32 c = 0; c < _model->GetAnimationCount(); c++)
		{
			void* ptr = (BYTE*)mallocPtr + c * pageSize;
			subResources[c].pSysMem = ptr;
			subResources[c].SysMemPitch = dataSize;
			subResources[c].SysMemSlicePitch = pageSize;
		}

		HRESULT hr = DEVICE->CreateTexture2D(&desc, subResources.data(), _texture.GetAddressOf());
		assert(SUCCEEDED(hr));

		::free(mallocPtr);
	}

	// Create ShaderResourceView
	{
		D3D11_SHADER_RESOURCE_VIEW_DESC	desc;
		ZeroMemory(&desc, sizeof(desc));
		desc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2DARRAY;
		desc.Texture2DArray.MipLevels = 1;
		desc.Texture2DArray.ArraySize = _model->GetAnimationCount();

		HRESULT hr = DEVICE->CreateShaderResourceView(_texture.Get(), &desc, _shaderResourceView.GetAddressOf());
		assert(SUCCEEDED(hr));
	}
}

void ModelAnimator::CreateAniamtionTransform(uint32 index)
{
	using namespace std;

	vector<Matrix> tempAnimationBoneTransforms(MAX_MODEL_TRANSFORMS, Matrix::Identity);

	shared_ptr<ModelAnimation> animation = _model->GetAnimationByIndex(index);
	for (uint32 frameIndex = 0; frameIndex < animation->frameCount; frameIndex++)
	{
		for (uint32 boneIndex = 0; boneIndex < _model->GetBoneCount(); boneIndex++)
		{
			const shared_ptr<ModelBone>& bone = _model->GetBoneByIndex(boneIndex);
			
			Matrix matAnimation;

			shared_ptr<ModelKeyframe> keyframe = animation->GetKeyframe(bone->name);
			if (keyframe != nullptr)
			{
				ModelKeyframeData& data = keyframe->transforms[frameIndex];

				Matrix matScale = Matrix::CreateScale(data.scale);
				Matrix matRotation = Matrix::CreateFromQuaternion(data.rotation);
				Matrix matTranslation = Matrix::CreateTranslation(data.translation);

				matAnimation = matScale * matRotation * matTranslation;
			}
			else
			{
				matAnimation = Matrix::Identity;
			}

			// Local to Global transformation
			Matrix toRootMatrix = bone->transform;

			// Global to Local transformation
			Matrix invGlobal = toRootMatrix.Invert();

			int32 parentIndex = bone->parentIndex;
			Matrix matParent = Matrix::Identity;
			if (parentIndex >= 0)
			{
				matParent = tempAnimationBoneTransforms[parentIndex];
			}

			tempAnimationBoneTransforms[boneIndex] = matAnimation * matParent;

			_animationTransforms[index].transforms[frameIndex][boneIndex] = invGlobal * tempAnimationBoneTransforms[boneIndex];
		}
	}
}
