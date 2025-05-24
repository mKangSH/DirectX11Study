#include "pch.h"
#include "RenderManager.h"
#include "../04.Component/Camera.h"

void RenderManager::Init(std::shared_ptr<Shader> shader)
{
	_shader = shader;

	_globalBuffer = std::make_shared<ConstantBuffer<GlobalDesc>>();
	_globalBuffer->CreateBuffer();
	_globalEffectBuffer = _shader->GetConstantBuffer("GlobalBuffer");

	_transformBuffer = std::make_shared<ConstantBuffer<TransformDesc>>();
	_transformBuffer->CreateBuffer();
	_transformEffectBuffer = _shader->GetConstantBuffer("TransformBuffer");

	_lightBuffer = std::make_shared<ConstantBuffer<LightDesc>>();
	_lightBuffer->CreateBuffer();
	_lightEffectBuffer = _shader->GetConstantBuffer("LightBuffer");

	_materialBuffer = std::make_shared<ConstantBuffer<MaterialDesc>>();
	_materialBuffer->CreateBuffer();
	_materialEffectBuffer = _shader->GetConstantBuffer("MaterialBuffer");

	_boneBuffer = std::make_shared<ConstantBuffer<BoneDesc>>();
	_boneBuffer->CreateBuffer();
	_boneEffectBuffer = _shader->GetConstantBuffer("BoneBuffer");
}

void RenderManager::Update()
{
	UploadGlobalDesc(Camera::S_MatView, Camera::S_MatProjection);
}

void RenderManager::UploadGlobalDesc(const Matrix& view, const Matrix& projection)
{
	_globalDesc.View = view;
	_globalDesc.Projection = projection;
	_globalDesc.ViewProjection = view * projection;
	_globalDesc.ViewInverse = view.Invert();
	
	_globalBuffer->UpdateBuffer(_globalDesc);
	_globalEffectBuffer->SetConstantBuffer(_globalBuffer->GetConstantBuffer().Get());
}

void RenderManager::UploadTransformDesc(const TransformDesc& desc)
{
	_transformDesc = desc;

	_transformBuffer->UpdateBuffer(_transformDesc);
	_transformEffectBuffer->SetConstantBuffer(_transformBuffer->GetConstantBuffer().Get());
}

void RenderManager::UploadLightDesc(const LightDesc& desc)
{
	_lightDesc = desc;

	_lightBuffer->UpdateBuffer(_lightDesc);
	_lightEffectBuffer->SetConstantBuffer(_lightBuffer->GetConstantBuffer().Get());
}

void RenderManager::UploadMaterialDesc(const MaterialDesc& desc)
{
	_materialDesc = desc;

	_materialBuffer->UpdateBuffer(_materialDesc);
	_materialEffectBuffer->SetConstantBuffer(_materialBuffer->GetConstantBuffer().Get());
}

void RenderManager::UploadBoneDesc(const BoneDesc& desc)
{
	_boneDesc = desc;

	_boneBuffer->UpdateBuffer(_boneDesc);
	_boneEffectBuffer->SetConstantBuffer(_boneBuffer->GetConstantBuffer().Get());
}
