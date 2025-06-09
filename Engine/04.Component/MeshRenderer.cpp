#include "pch.h"
#include "MeshRenderer.h"
#include "../00.Engine/Resource/Texture.h"
#include "../00.Engine/Resource/Mesh.h"
#include "../00.Engine/Resource/Material.h"
#include "../01.Graphics/Shader/Shader.h"
#include "../04.Component/Camera.h"

MeshRenderer::MeshRenderer() : Super(ComponentType::MeshRenderer)
{
}

MeshRenderer::~MeshRenderer()
{
}

void MeshRenderer::Update()
{
	if (_mesh == nullptr || _material == nullptr)
	{
		return;
	}

	std::shared_ptr<Shader> shader = _material->GetShader();
	if (shader == nullptr)
	{
		return;
	}

	_material->Update();

	Matrix world = GetTransform()->GetWorldMatrix();
	RENDER->UploadTransformDesc(TransformDesc(world));

	uint32 stride = _mesh->GetVertexBuffer()->GetStride();
	uint32 offset = _mesh->GetVertexBuffer()->GetOffset();

	DEVICECONTEXT->IASetVertexBuffers(0, 1, _mesh->GetVertexBuffer()->GetBuffer().GetAddressOf(), &stride, &offset);
	DEVICECONTEXT->IASetIndexBuffer(_mesh->GetIndexBuffer()->GetBuffer().Get(), DXGI_FORMAT_R32_UINT, 0);

	RasterizerType rasterizerType = RENDER->GetRasterizerState();
	if (_pass != 255)
	{
		shader->DrawIndexed(_technique, _pass, _mesh->GetIndexBuffer()->GetCount(), 0, 0);
	}
	else
	{
		shader->DrawIndexed(_technique, static_cast<UINT>(rasterizerType), _mesh->GetIndexBuffer()->GetCount(), 0, 0);
	}
}