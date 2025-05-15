#include "pch.h"
#include "10. GlobalTestDemo.h"
#include "Engine/00.Engine/Resource/ResourceBase.h"
#include "Engine/00.Engine/Resource/Texture.h"
#include "Engine/00.Engine/Resource/Mesh.h"
#include "Engine/03.SceneObject/SceneObject.h"
#include "Engine/04.Component/Camera.h"
#include "Engine/04.Component/MeshRenderer.h"
#include "../Main/Camera/CameraScript.h"

void GlobalTestDemo::Init()
{
	RESOURCES->Init(L"..\\Resources\\");

	// Camera
	_mainCamera = std::make_shared<SceneObject>();
	_mainCamera->GetOrAddTransform()->SetPosition(Vec3(0.0f, 0.0f, -2.0f));
	std::shared_ptr<Camera> perspectiveCamera = std::make_shared<Camera>();
	_mainCamera->AddComponent(perspectiveCamera);
	_mainCamera->AddComponent(std::make_shared<CameraScript>());

	// Object
	_object = std::make_shared<SceneObject>();
	_object->GetOrAddTransform();
	_object->AddComponent(std::make_shared<MeshRenderer>());
	{
		std::shared_ptr<Shader> shader = std::make_shared<Shader>(L"07. Normal.fx");
		_object->GetMeshRenderer()->SetShader(shader);
		_shader = shader;
	}
	{
		std::shared_ptr<Mesh> mesh = RESOURCES->Get<Mesh>(L"Sphere");
		_object->GetMeshRenderer()->SetMesh(mesh);
	}
	{
		std::shared_ptr<Texture> texture = RESOURCES->Load<Texture>(L"Background", L"Textures\\Background.png");
		_object->GetMeshRenderer()->SetTexture(texture);
	}

	_lightDirectionVariable = _shader->GetVector("LightDirection");
}

void GlobalTestDemo::Update()
{
	if (INPUT->GetButtonDown(KEY_TYPE::TAB))
	{
		_rasterizerType = (_rasterizerType == RasterizerType::SOLID) ? RasterizerType::WIREFRAME : RasterizerType::SOLID;
	}
	_mainCamera->Update();
	_object->Update();
}

void GlobalTestDemo::Render()
{
	_lightDirectionVariable->SetFloatVector((float*)&_lightDirection);

}
