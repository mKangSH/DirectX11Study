#include "pch.h"
#include "12. AmbientDemo.h"
#include "Engine/00.Engine/Resource/ResourceBase.h"
#include "Engine/00.Engine/Resource/Texture.h"
#include "Engine/00.Engine/Resource/Mesh.h"
#include "Engine/03.SceneObject/SceneObject.h"
#include "Engine/04.Component/Camera.h"
#include "Engine/04.Component/MeshRenderer.h"
#include "../Main/Camera/CameraScript.h"

void AmbientDemo::Init()
{
	RESOURCES->Init(L"..\\Resources\\");

	_shader = std::make_shared<Shader>(L"01.Beginner\\09. Lighting_Ambient.fx");
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

void AmbientDemo::Update()
{
	if (INPUT->GetButtonDown(KEY_TYPE::TAB))
	{
		_rasterizerType = (_rasterizerType == RasterizerType::SOLID) ? RasterizerType::WIREFRAME : RasterizerType::SOLID;
	}

	_mainCamera->Update();
	RENDER->Update();

	Vec4 lightAmbient(0.2f, 0.1f, 0.1f, 1.0f);
	_shader->GetVector("LightAmbient")->SetFloatVector((float*)&lightAmbient);

	{
		Vec4 materialAmbient(1.0f);
		_shader->GetVector("MaterialAmbient")->SetFloatVector((float*)&materialAmbient);
		_object->Update();
	}
	
	{
		Vec4 materialAmbient(1.0f);
		_shader->GetVector("MaterialAmbient")->SetFloatVector((float*)&materialAmbient);
		_object2->Update();
	}
}

void AmbientDemo::Render()
{

}
