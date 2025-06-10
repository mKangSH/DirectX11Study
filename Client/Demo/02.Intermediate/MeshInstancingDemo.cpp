#include "pch.h"
#include "MeshInstancingDemo.h"
#include "Engine/00.Engine/Resource/ResourceBase.h"
#include "Engine/00.Engine/Resource/Texture.h"
#include "Engine/00.Engine/Resource/Mesh.h"
#include "Engine/00.Engine/Resource/Material.h"
#include "Engine/04.Component/Camera.h"
#include "Engine/04.Component/MeshRenderer.h"
#include "../Main/Camera/CameraScript.h"

void MeshInstancingDemo::Init()
{
	RESOURCES->Init(L"");
	_shader = std::make_shared<Shader>(L"02.Intermediate\\20. MeshInstancingDemo.fx");
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
	}

	for(int i = 0; i < 10000; ++i)
	{
		auto object = std::make_shared<SceneObject>();
		object->GetOrAddTransform()->SetPosition(Vec3(rand() % 100, 0.0f, rand() % 100));
		object->AddComponent(std::make_shared<MeshRenderer>());
		{
			object->GetMeshRenderer()->SetMaterial(RESOURCES->Get<Material>(L"Background"));
		}
		{
			auto mesh = RESOURCES->Get<Mesh>(L"Sphere");
			object->GetMeshRenderer()->SetMesh(mesh);
		}

		_objects.push_back(object);
	}
}

void MeshInstancingDemo::Update()
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

	INSTANCING->Render(_objects);

	_mainCamera->Update();
	RENDER->Update();
}

void MeshInstancingDemo::Render()
{
}
