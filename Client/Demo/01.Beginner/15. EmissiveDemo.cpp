#include "pch.h"
#include "15. EmissiveDemo.h"
#include "Engine/00.Engine/Resource/ResourceBase.h"
#include "Engine/00.Engine/Resource/Texture.h"
#include "Engine/00.Engine/Resource/Mesh.h"
#include "Engine/03.SceneObject/SceneObject.h"
#include "Engine/04.Component/Camera.h"
#include "Engine/04.Component/MeshRenderer.h"
#include "../Main/Camera/CameraScript.h"

void EmissiveDemo::Init()
{
	RESOURCES->Init(L"..\\Resources\\");

	_shader = std::make_shared<Shader>(L"01.Beginner\\12. Lighting_Emissive.fx");
	RENDER->Init(_shader);

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
		_object->GetMeshRenderer()->SetShader(_shader);
	}
	{
		std::shared_ptr<Mesh> mesh = RESOURCES->Get<Mesh>(L"Sphere");
		_object->GetMeshRenderer()->SetMesh(mesh);
	}
	{
		std::shared_ptr<Texture> texture = RESOURCES->Load<Texture>(L"Background", L"Textures\\Background.png");
		_object->GetMeshRenderer()->SetTexture(texture);
	}

	// Object2
	_object2 = std::make_shared<SceneObject>();
	_object2->GetOrAddTransform()->SetPosition(Vec3{0.5f, 0.0f, 2.0f});
	_object2->AddComponent(std::make_shared<MeshRenderer>());
	{
		_object2->GetMeshRenderer()->SetShader(_shader);
	}
	{
		std::shared_ptr<Mesh> mesh = RESOURCES->Get<Mesh>(L"Cube");
		_object2->GetMeshRenderer()->SetMesh(mesh);
	}
	{
		std::shared_ptr<Texture> texture = RESOURCES->Load<Texture>(L"Background", L"Textures\\Background.png");
		_object2->GetMeshRenderer()->SetTexture(texture);
	}
}

void EmissiveDemo::Update()
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
		Vec4 material(1.f, 0.f, 1.f, 1.f);
		_shader->GetVector("MaterialEmissive")->SetFloatVector((float*)&material);
		_object->Update();
	}
	
	{
		Vec4 material(1.f, 1.f, 0.f, 1.f);
		_shader->GetVector("MaterialEmissive")->SetFloatVector((float*)&material);
		_object2->Update();
	}

	_mainCamera->Update();
	RENDER->Update();
}

void EmissiveDemo::Render()
{

}
