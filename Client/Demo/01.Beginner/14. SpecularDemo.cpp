#include "pch.h"
#include "14. SpecularDemo.h"
#include "Engine/00.Engine/Resource/ResourceBase.h"
#include "Engine/00.Engine/Resource/Texture.h"
#include "Engine/00.Engine/Resource/Mesh.h"
#include "Engine/03.SceneObject/SceneObject.h"
#include "Engine/04.Component/Camera.h"
#include "Engine/04.Component/MeshRenderer.h"
#include "../Main/Camera/CameraScript.h"

void SpecularDemo::Init()
{
	RESOURCES->Init(L"..\\Resources\\");

	_shader = std::make_shared<Shader>(L"01.Beginner\\11. Lighting_Specular.fx");
	RENDER->Init(_shader);

	// Camera
	_mainCamera = std::make_shared<SceneObject>();
	_mainCamera->GetOrAddTransform()->SetPosition(Vec3(0.0f, 0.0f, -10.0f));
	std::shared_ptr<Camera> perspectiveCamera = std::make_shared<Camera>();
	_mainCamera->AddComponent(perspectiveCamera);
	_mainCamera->AddComponent(std::make_shared<CameraScript>());

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

void SpecularDemo::Update()
{
	if (INPUT->GetButtonDown(KEY_TYPE::TAB))
	{
		_rasterizerType = (_rasterizerType == RasterizerType::SOLID) ? RasterizerType::WIREFRAME : RasterizerType::SOLID;
	}

	_mainCamera->Update();
	RENDER->Update();

	Vec4 lightSpecular(1.f, 1.f, 1.f, 1.f);
	_shader->GetVector("LightSpecular")->SetFloatVector((float*)&lightSpecular);

	Vec3 lightDirection(1.0f, -1.0f, 0.0f);
	lightDirection.Normalize();
	_shader->GetVector("LightDirection")->SetFloatVector((float*)&lightDirection);

	{
		Vec4 materialSpecular(1.f, 0.f, 1.f, 1.f);
		_shader->GetVector("MaterialSpecular")->SetFloatVector((float*)&materialSpecular);
		_object->Update();
	}
	
	{
		Vec4 materialSpecular(1.f, 0.f, 1.f, 1.f);
		_shader->GetVector("MaterialSpecular")->SetFloatVector((float*)&materialSpecular);
		_object2->Update();
	}
}

void SpecularDemo::Render()
{

}
