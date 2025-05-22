#include "pch.h"
#include "ModelRenderer.h"
#include "../00.Engine/Resource/Material.h"
#include "../00.Engine/Resource/Model/Model.h"
#include "../00.Engine/Resource/Model/ModelMesh.h"

ModelRenderer::ModelRenderer(std::shared_ptr<Shader> shader)
	: Super(ComponentType::ModelRenderer), _shader(shader)
{
}

ModelRenderer::~ModelRenderer()
{
}

void ModelRenderer::Update()
{
	if (_model == nullptr)
	{
		return;
	}
	
	Matrix world = GetTransform()->GetWorldMatrix();
	RENDER->UploadTransformDesc(TransformDesc{ world });
		
	const auto& meshes = _model->GetMeshes();
	for (auto& mesh : meshes)
	{
		if (mesh->material)
		{
			mesh->material->Update();
		}

		uint32 stride = mesh->vertexBuffer->GetStride();
		uint32 offset = mesh->vertexBuffer->GetOffset();

		DEVICECONTEXT->IASetVertexBuffers(0, 1, mesh->vertexBuffer->GetBuffer().GetAddressOf(), &stride, &offset);
		DEVICECONTEXT->IASetIndexBuffer(mesh->indexBuffer->GetBuffer().Get(), DXGI_FORMAT_R32_UINT, 0);

		_shader->DrawIndexed(0, _pass, mesh->indexBuffer->GetCount(), 0, 0);
	}
}

void ModelRenderer::SetModel(std::shared_ptr<Model> model)
{
	_model = model;

	const auto& materials = _model->GetMaterials();
	for (auto& material : materials)
	{
		material->SetShader(_shader);
	}
}
