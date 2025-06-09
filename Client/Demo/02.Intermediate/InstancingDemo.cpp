#include "pch.h"
#include "InstancingDemo.h"
#include "Engine/00.Engine/Resource/ResourceBase.h"
#include "Engine/00.Engine/Resource/Texture.h"
#include "Engine/00.Engine/Resource/Mesh.h"
#include "Engine/00.Engine/Resource/Material.h"
#include "Engine/04.Component/Camera.h"
#include "Engine/04.Component/MeshRenderer.h"
#include "../Main/Camera/CameraScript.h"

void InstancingDemo::Init()
{
	RESOURCES->Init(L"");
	_shader = std::make_shared<Shader>(L"02.Intermediate\\19. InstancingDemo.fx");
	RENDER->Init(_shader);

	// Camera
	_mainCamera = std::make_shared<SceneObject>();
	_mainCamera->GetOrAddTransform()->SetPosition(Vec3(0.0f, 0.0f, -5.0f));
	std::shared_ptr<Camera> perspectiveCamera = std::make_shared<Camera>();
	_mainCamera->AddComponent(perspectiveCamera);
	_mainCamera->AddComponent(std::make_shared<CameraScript>());
	_mainCamera->Start();

	// Material
	{
		std::shared_ptr<Material> material = std::make_shared<Material>();
		{
			material->SetShader(_shader);
		}
		{
			std::shared_ptr<Texture> texture = RESOURCES->Load<Texture>(L"Background", L"..\\Resources\\Textures\\Background.png");
			material->SetDiffuseMap(texture);
		}

		MaterialDesc& desc = material->GetMaterialDesc();
		desc.ambient = Vec4(1.0f);
		desc.diffuse = Vec4(1.0f);
		desc.specular = Vec4(1.0f);

		RESOURCES->Add(L"Background", material);

		// Instancing
		_material = material;
	}

	for(int i = 0; i < 100000; ++i)
	{
		auto object = std::make_shared<SceneObject>();
		object->GetOrAddTransform()->SetPosition(Vec3(rand() % 1000, 0.0f, rand() % 100));
		object->AddComponent(std::make_shared<MeshRenderer>());
		{
			object->GetMeshRenderer()->SetMaterial(RESOURCES->Get<Material>(L"Background"));
		}
		{
			auto mesh = RESOURCES->Get<Mesh>(L"Sphere");
			object->GetMeshRenderer()->SetMesh(mesh);

			// Instancing
			_mesh = mesh;
		}

		_objects.push_back(object);
	}

	// Instancing
	_instanceBuffer = std::make_shared<VertexBuffer>();

	for(auto& _object : _objects)
	{
		Matrix worldMatrix = _object->GetTransform()->GetWorldMatrix();
		_worldMatrices.push_back(worldMatrix);
	}

	_instanceBuffer->CreateBuffer(_worldMatrices, 1);
}

void InstancingDemo::Update()
{
	if (INPUT->GetButtonDown(KEY_TYPE::TAB))
	{
		if (RENDER->GetRasterizerState() == RasterizerType::WIREFRAME)
		{
			RENDER->SetRasterizerState(RasterizerType::SOLID);
		}
		else if (RENDER->GetRasterizerState() == RasterizerType::SOLID)
		{
			RENDER->SetRasterizerState(RasterizerType::WIREFRAME);
		}
	}

	{
		LightDesc lightDesc;
		lightDesc.ambient = Vec4(0.7f, 0.7f, 0.7f, 1.0f);
		lightDesc.diffuse = Vec4(1.0f, 1.0f, 1.0f, 1.0f);
		lightDesc.specular = Vec4(1.0f, 1.0f, 1.0f, 1.0f);
		lightDesc.emissive = Vec4(0.0f, 0.0f, 0.0f, 1.0f);
		lightDesc.direction = Vec3(0.0f, 0.0f, 1.0f);

		RENDER->UploadLightDesc(lightDesc);
	}

	/*for(auto& _object : _objects)
	{
		_object->Update();
	}*/

	_material->Update();

	/*Matrix world = GetTransform()->GetWorldMatrix();
	RENDER->UploadTransformDesc(TransformDesc(world));*/

	_mesh->GetVertexBuffer()->PushData();
	_instanceBuffer->PushData();
	_mesh->GetIndexBuffer()->PushData();
	
	RasterizerType rasterizerType = RENDER->GetRasterizerState();
	_shader->DrawIndexedInstanced(1, static_cast<UINT>(rasterizerType), _mesh->GetIndexBuffer()->GetCount(), _objects.size());

	_mainCamera->Update();
	RENDER->Update();
}

void InstancingDemo::Render()
{
}
