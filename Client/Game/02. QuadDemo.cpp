#include "pch.h"
#include "02. QuadDemo.h"
#include "Engine/01.Graphics/Buffer/GeometryHelper.h"

void QuadDemo::Init()
{
	_shader = std::make_shared<Shader>(L"02. Quad.fx");

	_geometry = std::make_shared<Geometry<VertexColorData>>();
	GeometryHelper::CreateQuad(_geometry, DirectX::Colors::Cyan);

	_vertexBuffer = std::make_shared<VertexBuffer>();
	_vertexBuffer->CreateBuffer(_geometry->GetVertices());

	_indexBuffer = std::make_shared<IndexBuffer>();
	_indexBuffer->CreateBuffer(_geometry->GetIndices());
}

void QuadDemo::Update()
{

}

void QuadDemo::Render()
{
	uint32 stride = _vertexBuffer->GetStride();
	uint32 offset = _vertexBuffer->GetOffset();

	DEVICECONTEXT->IASetVertexBuffers(0, 1, _vertexBuffer->GetBuffer().GetAddressOf(), &stride, &offset);
	DEVICECONTEXT->IASetIndexBuffer(_indexBuffer->GetBuffer().Get(), DXGI_FORMAT_R32_UINT, 0);

	_shader->DrawIndexed(0, 1, _indexBuffer->GetCount());
}
