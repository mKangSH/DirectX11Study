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

void MeshRenderer::RenderInstancing(std::shared_ptr<class InstancingBuffer>& buffer)
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

	_mesh->GetVertexBuffer()->PushData();
	_mesh->GetIndexBuffer()->PushData();

	buffer->PushDataToGPU();
	shader->DrawIndexedInstanced(1, _pass, _mesh->GetIndexBuffer()->GetCount(), buffer->GetCount());
}

const InstanceID MeshRenderer::GetInstanceID() const
{
	return std::make_pair((uint64)_mesh.get(), (uint64)_material.get());
}