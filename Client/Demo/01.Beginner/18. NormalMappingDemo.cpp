#include "pch.h"
#include "18. NormalMappingDemo.h"
#include "Engine/00.Engine/Resource/ResourceBase.h"
#include "Engine/00.Engine/Resource/Texture.h"
#include "Engine/00.Engine/Resource/Mesh.h"
#include "Engine/00.Engine/Resource/Material.h"
#include "Engine/03.SceneObject/SceneObject.h"
#include "Engine/04.Component/Camera.h"
#include "Engine/04.Component/MeshRenderer.h"
#include "../Main/Camera/CameraScript.h"

void NormalMappingDemo::Init()
{
	RESOURCES->Init(L"..\\Resources\\");

	_shader = std::make_shared<Shader>(L"01.Beginner\\14. NormalMapping.fx");
	RENDER->Init(_shader);

	// Material
	{
		std::shared_ptr<Material> material = std::make_shared<Material>();
		{
			material->SetShader(_shader);
		}
		{
			std::shared_ptr<Texture> texture = RESOURCES->Load<Texture>(L"Background", L"Textures\\Background.png");
			material->SetDiffuseMap(texture);
		}
		{
			std::shared_ptr<Texture> texture = RESOURCES->Load<Texture>(L"BlueIceNormal", L"Textures\\BlueIce_Normal.jpg");
			material->SetNormalMap(texture);
		}

		MaterialDesc& desc = material->GetMaterialDesc();
		desc.ambient = Vec4(0.7f);
		desc.diffuse = Vec4(0.5f);
		desc.specular = Vec4(0.5f);
		desc.emissive = Vec4(1.0f);

		RESOURCES->Add(L"Background", material);
	}
	
	// Camera
	_mainCamera = std::make_shared<SceneObject>();
	_mainCamera->GetOrAddTransform()->SetPosition(Vec3(0.0f, 0.0f, -10.0f));
	std::shared_ptr<Camera> perspectiveCamera = std::make_shared<Camera>();
	_mainCamera->AddComponent(perspectiveCamera);
	_mainCamera->AddComponent(std::make_shared<CameraScript>());

	_mainCamera->Start();

	// Object
	_object = std::make_shared<SceneObject>();
	_object->GetOrAddTransform();
	_object->AddComponent(std::make_shared<MeshRenderer>());
	{
		std::shared_ptr<Mesh> mesh = RESOURCES->Get<Mesh>(L"Sphere");
		_object->GetMeshRenderer()->SetMesh(mesh);
	}
	{
		std::shared_ptr<Material> material = RESOURCES->Get<Material>(L"Background");
		_object->GetMeshRenderer()->SetMaterial(material);
	}

	// Object2
	_object2 = std::make_shared<SceneObject>();
	_object2->GetOrAddTransform()->SetPosition(Vec3{0.5f, 0.0f, 2.0f});
	_object2->AddComponent(std::make_shared<MeshRenderer>());
	{
		std::shared_ptr<Mesh> mesh = RESOURCES->Get<Mesh>(L"Cube");
		_object2->GetMeshRenderer()->SetMesh(mesh);
	}
	{
		std::shared_ptr<Material> material = RESOURCES->Get<Material>(L"Background")->Clone();
		MaterialDesc& desc = material->GetMaterialDesc();

		_object2->GetMeshRenderer()->SetMaterial(material);
	}
}

void NormalMappingDemo::Update()
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
		lightDesc.emissive = Vec4(0.0f, 1.0f, 1.0f, 1.0f);
		lightDesc.direction = Vec3(1.0f, 0.0f, 1.0f);

		RENDER->UploadLightDesc(lightDesc);
	}

	{
		_object->Update();
		_object2->Update();
	}

	_mainCamera->Update();
	RENDER->Update();
}

void NormalMappingDemo::Render()
{

}

