#include "pch.h"
#include "TweenDemo.h"
#include "Engine/00.Engine/Resource/ResourceBase.h"
#include "Engine/00.Engine/Resource/Texture.h"
#include "Engine/00.Engine/Resource/Mesh.h"
#include "Engine/00.Engine/Resource/Material.h"
#include "Engine/00.Engine/Resource/Model/Model.h"
#include "Engine/03.SceneObject/SceneObject.h"
#include "Engine/04.Component/Camera.h"
#include "Engine/04.Component/MeshRenderer.h"
#include "Engine/04.Component/ModelRenderer.h"
#include "Engine/04.Component/ModelAnimator.h"
#include "../Utils/CameraScript.h"

void TweenDemo::Init()
{
	RESOURCES->Init(L"..\\Resources\\");
	_shader = std::make_shared<Shader>(L"02.Intermediate\\17. TweenDemo.fx");
	RENDER->Init(_shader);

	// Camera
	_mainCamera = std::make_shared<SceneObject>();
	_mainCamera->GetOrAddTransform()->SetPosition(Vec3(0.0f, 0.0f, -5.0f));
	std::shared_ptr<Camera> perspectiveCamera = std::make_shared<Camera>();
	_mainCamera->AddComponent(perspectiveCamera);
	_mainCamera->AddComponent(std::make_shared<CameraScript>());

	_mainCamera->Start();

	// Object
	CreateKachujin();
}

void TweenDemo::Update()
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
	}

	_mainCamera->Update();
	RENDER->Update();
}

void TweenDemo::Render()
{
}

void TweenDemo::CreateKachujin()
{
	std::shared_ptr<Model> model = std::make_shared<Model>();
	model->ReadModel(L"Kachujin/Kachujin");
	model->ReadMaterial(L"Kachujin/Kachujin");
	model->ReadAnimation(L"Kachujin/Idle");
	model->ReadAnimation(L"Kachujin/Run");
	model->ReadAnimation(L"Kachujin/Slash");

	_object = std::make_shared<SceneObject>();
	_object->GetOrAddTransform()->SetPosition(Vec3(0, 0, 1));
	_object->GetOrAddTransform()->SetScale(Vec3(0.01f));

	_object->AddComponent(std::make_shared<ModelAnimator>(_shader));
	{
		_object->GetModelAnimator()->SetModel(model);
		_object->GetModelAnimator()->SetPass(3);
	}
}

void TweenDemo::CreateWolf()
{
	std::shared_ptr<Model> model = std::make_shared<Model>();
	model->ReadModel(L"Wolf/Wolf");
	model->ReadMaterial(L"Wolf/Wolf");

	_object = std::make_shared<SceneObject>();
	_object->GetOrAddTransform()->SetPosition(Vec3(0, 0, 50));
	_object->GetOrAddTransform()->SetScale(Vec3(25.f));

	_object->AddComponent(std::make_shared<ModelRenderer>(_shader));
	{
		_object->GetModelRenderer()->SetModel(model);
		//_object->GetModelRenderer()->SetPass(3);
	}
}

void TweenDemo::CreateTower()
{
	std::shared_ptr<Model> model = std::make_shared<Model>();
	model->ReadModel(L"Tower/Tower");
	model->ReadMaterial(L"Tower/Tower");

	_object = std::make_shared<SceneObject>();
	_object->GetOrAddTransform()->SetPosition(Vec3(0, 0, 50));
	_object->GetOrAddTransform()->SetScale(Vec3(1.f));

	_object->AddComponent(std::make_shared<ModelRenderer>(_shader));
	{
		_object->GetModelRenderer()->SetModel(model);
		_object->GetModelRenderer()->SetPass(3);
	}
}

void TweenDemo::CreateTank()
{
	std::shared_ptr<Model> model = std::make_shared<Model>();
	model->ReadModel(L"Tank/Tank");
	model->ReadMaterial(L"Tank/Tank");

	_object = std::make_shared<SceneObject>();
	_object->GetOrAddTransform()->SetPosition(Vec3(0, 0, 50));
	_object->GetOrAddTransform()->SetScale(Vec3(1.f));

	_object->AddComponent(std::make_shared<ModelRenderer>(_shader));
	{
		_object->GetModelRenderer()->SetModel(model);
		_object->GetModelRenderer()->SetPass(2);
	}
}
