#include "pch.h"
#include "06. SamplerDemo.h"
#include "Engine/00.Engine/Resource/ResourceBase.h"
#include "Engine/00.Engine/Resource/Texture.h"
#include "Engine/01.Graphics/Buffer/GeometryHelper.h"
#include "Engine/04.Component/Component.h"
#include "Engine/03.SceneObject/SceneObject.h"
#include "Engine/04.Component/Camera.h"
#include "../Main/Camera/CameraScript.h"

void SamplerDemo::Init()
{
	_shader = std::make_shared<Shader>(L"05. Sampler.fx");

	RESOURCES->Init(L"..\\Resources\\");

	_geometry = std::make_shared<Geometry<VertexTextureData>>();
	GeometryHelper::CreateGrid(_geometry, 20, 20);

	_vertexBuffer = std::make_shared<VertexBuffer>();
	_vertexBuffer->CreateBuffer(_geometry->GetVertices());

	_indexBuffer = std::make_shared<IndexBuffer>();
	_indexBuffer->CreateBuffer(_geometry->GetIndices());

	_worldVariable = _shader->GetMatrix("World");
	_viewVariable = _shader->GetMatrix("View");
	_projectionVariable = _shader->GetMatrix("Projection");

	// Camera
	_mainCamera = std::make_shared<SceneObject>();
	_mainCamera->GetOrAddTransform()->SetPosition(Vec3(0.0f, 0.0f, -2.0f));
	std::shared_ptr<Camera> perspectiveCamera = std::make_shared<Camera>();
	_mainCamera->AddComponent(perspectiveCamera);
	_mainCamera->AddComponent(std::make_shared<CameraScript>());

	_texture = RESOURCES->Load<Texture>(L"Scimitar", L"Textures\\Background.png");

	_textureVariable = _shader->GetSRV("Texture0");

	_addressVariable = _shader->GetScalar("Address");
}

void SamplerDemo::Update()
{
	if (INPUT->GetButtonDown(KEY_TYPE::TAB))
	{
		_rasterizerType = (_rasterizerType == RasterizerType::SOLID) ? RasterizerType::WIREFRAME : RasterizerType::SOLID;
	}

	if (INPUT->GetButtonDown(KEY_TYPE::RIGHT))
	{
		_addressType = static_cast<AddressType>((static_cast<int>(_addressType) + 1) % 4);
	}

	_mainCamera->Update();
}

void SamplerDemo::Render()
{
	_addressVariable->SetInt(_addressType);
	_worldVariable->SetMatrix((float*)&_world);
	_viewVariable->SetMatrix((float*)&Camera::S_MatView);
	_projectionVariable->SetMatrix((float*)&Camera::S_MatProjection);
	_textureVariable->SetResource(_texture->GetShaderResourceView().Get());

	uint32 stride = _vertexBuffer->GetStride();
	uint32 offset = _vertexBuffer->GetOffset();

	DEVICECONTEXT->IASetVertexBuffers(0, 1, _vertexBuffer->GetBuffer().GetAddressOf(), &stride, &offset);
	DEVICECONTEXT->IASetIndexBuffer(_indexBuffer->GetBuffer().Get(), DXGI_FORMAT_R32_UINT, 0);

	_shader->DrawIndexed(0, static_cast<UINT>(_rasterizerType), _indexBuffer->GetCount(), 0, 0);
}
