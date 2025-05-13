#include "pch.h"
#include "MeshRenderer.h"
#include "../00.Engine/Resource/Texture.h"
#include "../00.Engine/Resource/Mesh.h"
#include "../01.Graphics/Shader/Shader.h"
#include "../04.Component/Camera.h"

MeshRenderer::MeshRenderer() : Super(ComponentType::MeshRenderer)
{
}

MeshRenderer::~MeshRenderer()
{
}

void MeshRenderer::SetShader(std::shared_ptr<Shader> shader)
{
	_shader = shader;
	_worldVariable = _shader->GetMatrix("World");
	_viewVariable = _shader->GetMatrix("View");
	_projectionVariable = _shader->GetMatrix("Projection");
	_textureVariable = _shader->GetSRV("Texture0");
}

void MeshRenderer::Update()
{
	if (_mesh == nullptr || _shader == nullptr || _texture == nullptr)
	{
		return;
	}
	
	Matrix world = GetTransform()->GetWorldMatrix();
	_worldVariable->SetMatrix((float*)&world);
	_viewVariable->SetMatrix((float*)&Camera::S_MatView);
	_projectionVariable->SetMatrix((float*)&Camera::S_MatProjection);
	_textureVariable->SetResource(_texture->GetShaderResourceView().Get());

	uint32 stride = _mesh->GetVertexBuffer()->GetStride();
	uint32 offset = _mesh->GetVertexBuffer()->GetOffset();

	DEVICECONTEXT->IASetVertexBuffers(0, 1, _mesh->GetVertexBuffer()->GetBuffer().GetAddressOf(), &stride, &offset);
	DEVICECONTEXT->IASetIndexBuffer(_mesh->GetIndexBuffer()->GetBuffer().Get(), DXGI_FORMAT_R32_UINT, 0);

	_shader->DrawIndexed(0, 0, _mesh->GetIndexBuffer()->GetCount(), 0, 0);
}