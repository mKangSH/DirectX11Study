#include "pch.h"
#include "17. MaterialDemo.h"
#include "Engine/00.Engine/Resource/ResourceBase.h"
#include "Engine/00.Engine/Resource/Texture.h"
#include "Engine/00.Engine/Resource/Mesh.h"
#include "Engine/00.Engine/Resource/Material.h"
#include "Engine/03.SceneObject/SceneObject.h"
#include "Engine/04.Component/Camera.h"
#include "Engine/04.Component/MeshRenderer.h"
#include "../Main/Camera/CameraScript.h"

void MaterialDemo::Init()
{
	RESOURCES->Init(L"..\\Resources\\");

	_shader = std::make_shared<Shader>(L"01.Beginner\\13. Lighting.fx");
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

		MaterialDesc& desc = material->GetMaterialDesc();
		desc.ambient = Vec4(1.0f);
		desc.diffuse = Vec4(1.0f);

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
		// Resource의 경우 모든 리소스가 한 번 로드되어 공통으로 사용하기 때문에 
		// 개별 물체를 수정하기 위해 리소스 자체를 수정하게 된다면 전체가 수정된다.
		std::shared_ptr<Material> material = RESOURCES->Get<Material>(L"Background")->Clone();

		// 만약 아래의 내용 따로 넣어주고 싶다면 Clone을 하여 생성하고 Clone을 이용하여 추가하고 렌더링 해야 한다.
		MaterialDesc& desc = material->GetMaterialDesc();
		desc.ambient = Vec4(1.0f, 0.0f, 0.0f, 1.0f);
		desc.diffuse = Vec4(0.2f);

		_object2->GetMeshRenderer()->SetMaterial(material);
	}
}

void MaterialDemo::Update()
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

	{
		_object->Update();
		_object2->Update();
	}

	_mainCamera->Update();
	RENDER->Update();
}

void MaterialDemo::Render()
{

}
