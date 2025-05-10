#include "pch.h"
#include "03. ConstBufferDemo.h"
#include "Engine/01.Graphics/Buffer/GeometryHelper.h"

void ConstBufferDemo::Init()
{
	_shader = std::make_shared<Shader>(L"03. ConstBuffer.fx");

	_geometry = std::make_shared<Geometry<VertexColorData>>();
	GeometryHelper::CreateQuad(_geometry, DirectX::Colors::Cyan);

	_vertexBuffer = std::make_shared<VertexBuffer>();
	_vertexBuffer->CreateBuffer(_geometry->GetVertices());

	_indexBuffer = std::make_shared<IndexBuffer>();
	_indexBuffer->CreateBuffer(_geometry->GetIndices());

	_worldVariable = _shader->GetMatrix("World");
	_viewVariable = _shader->GetMatrix("View");
	_projectionVariable = _shader->GetMatrix("Projection");
}

void ConstBufferDemo::Update()
{
	float deltaTime = TIME->GetDeltaTime();

	if (INPUT->GetButtonDown(KEY_TYPE::TAB))
	{
		_rasterizerType = (_rasterizerType == RasterizerType::SOLID) ? RasterizerType::WIREFRAME : RasterizerType::SOLID;
	}

	if (INPUT->GetButton(KEY_TYPE::A))
	{
		_translation.x -= 3.f * deltaTime;
	}

	if (INPUT->GetButton(KEY_TYPE::D))
	{
		_translation.x += 3.f * deltaTime;
	}

	if (INPUT->GetButton(KEY_TYPE::W))
	{
		_translation.y += 3.f * deltaTime;
	}

	if (INPUT->GetButton(KEY_TYPE::S))
	{
		_translation.y -= 3.f * deltaTime;
	}

	// SRT
	_world = Matrix::CreateTranslation(_translation);
}

void ConstBufferDemo::Render()
{
	_worldVariable->SetMatrix((float*)&_world);
	_viewVariable->SetMatrix((float*)&_view);
	_projectionVariable->SetMatrix((float*)&_projection);

	uint32 stride = _vertexBuffer->GetStride();
	uint32 offset = _vertexBuffer->GetOffset();

	DEVICECONTEXT->IASetVertexBuffers(0, 1, _vertexBuffer->GetBuffer().GetAddressOf(), &stride, &offset);
	DEVICECONTEXT->IASetIndexBuffer(_indexBuffer->GetBuffer().Get(), DXGI_FORMAT_R32_UINT, 0);

	_shader->DrawIndexed(0, static_cast<UINT>(_rasterizerType), _indexBuffer->GetCount());
}
