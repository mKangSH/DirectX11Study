#include "pch.h"
#include "ImGuiDemo_TSoD.h"
#include "Engine/00.Engine/Resource/ResourceBase.h"
#include "Engine/00.Engine/Resource/Texture.h"
#include "Engine/00.Engine/Resource/Mesh.h"
#include "Engine/00.Engine/Resource/Material.h"
#include "Engine/00.Engine/Resource/Model/Model.h"
#include "Engine/03.SceneObject/SceneObject.h"
#include "Engine/04.Component/Camera.h"
#include "Engine/04.Component/MeshRenderer.h"
#include "Engine/04.Component/ModelRenderer.h"
#include "Camera/CameraScript.h"
#include "../UI/UIComponentBase.h"
#include "../Manager/LayoutManager.h"

void ImGuiDemo_TSoD::Init()
{
	RESOURCES->Init(L"");
	_shader = std::make_shared<Shader>(L"..\\Shaders\\02.Intermediate\\15. ModelDemo.fx");
	RENDER->Init(_shader);

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
		{
			std::shared_ptr<Texture> texture = RESOURCES->Load<Texture>(L"BlueIceNormal", L"..\\Resources\\Textures\\BlueIce_Normal.jpg");
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
	_mainCamera->GetOrAddTransform()->SetPosition(Vec3(0.0f, 10.0f, -10.0f));
	std::shared_ptr<Camera> perspectiveCamera = std::make_shared<Camera>();
	_mainCamera->AddComponent(perspectiveCamera);
	_mainCamera->AddComponent(std::make_shared<CameraScript>());

	_mainCamera->Start();

	// Object
	_sphere = std::make_shared<SceneObject>();
	_sphere->GetOrAddTransform()->SetPosition(Vec3{ 0.0f, 0.0f, 50.0f });
	_sphere->GetOrAddTransform()->SetScale(Vec3(10.0f));
	_sphere->AddComponent(std::make_shared<MeshRenderer>());
	{
		std::shared_ptr<Mesh> mesh = RESOURCES->Get<Mesh>(L"Sphere");
		_sphere->GetMeshRenderer()->SetMesh(mesh);
	}
	{
		std::shared_ptr<Material> material = RESOURCES->Get<Material>(L"Background");
		_sphere->GetMeshRenderer()->SetMaterial(material);
	}

	// Object2
	_cube = std::make_shared<SceneObject>();
	_cube->GetOrAddTransform()->SetPosition(Vec3{ 0.0f, 0.0f, 50.0f });
	_cube->GetTransform()->SetScale(Vec3(10.0f));
	_cube->AddComponent(std::make_shared<MeshRenderer>());
	{
		std::shared_ptr<Mesh> mesh = RESOURCES->Get<Mesh>(L"Cube");
		_cube->GetMeshRenderer()->SetMesh(mesh);
	}
	{
		std::shared_ptr<Material> material = RESOURCES->Get<Material>(L"Background")->Clone();
		MaterialDesc& desc = material->GetMaterialDesc();

		_cube->GetMeshRenderer()->SetMaterial(material);
	}

	// Object
	CreateWolf();
	CreateTower();
	CreateTank();

	_layoutManager = std::make_shared<LayoutManager>();
	_layoutManager->Init();
}

void ImGuiDemo_TSoD::Update()
{
	{
		LightDesc lightDesc;
		lightDesc.ambient = Vec4(0.7f, 0.7f, 0.7f, 1.0f);
		lightDesc.diffuse = Vec4(1.0f, 1.0f, 1.0f, 1.0f);
		lightDesc.specular = Vec4(1.0f, 1.0f, 1.0f, 1.0f);
		lightDesc.emissive = Vec4(0.0f, 1.0f, 1.0f, 1.0f);
		lightDesc.direction = Vec3(1.0f, 0.0f, 1.0f);

		RENDER->UploadLightDesc(lightDesc);
	}

	// TODO : Transform 테스트 해볼까요

	switch (_layoutManager->GetSelected())
	{
		case 0:
			{
				_wolf->Update();
			}
			break;
		case 1:
			{
				_tower->Update();
			}
			break;
		case 2:
			{
				_tank->Update();
			}
			break;
		case 3:
			{
				_sphere->Update();
			}
			break;
		case 4:
			{
				_cube->Update();
			}
			break;
	}

	_mainCamera->Update();
	RENDER->Update();
}

void ImGuiDemo_TSoD::Render()
{
}

void ImGuiDemo_TSoD::ImGuiRender()
{
	_layoutManager->Update();
	_layoutManager->Render();
}

void ImGuiDemo_TSoD::CreateWolf()
{
	std::shared_ptr<Model> model = std::make_shared<Model>();
	model->ReadModel(L"Wolf/Wolf");
	model->ReadMaterial(L"Wolf/Wolf");

	_wolf = std::make_shared<SceneObject>();
	_wolf->GetOrAddTransform()->SetPosition(Vec3(0, 0, 50));
	_wolf->GetOrAddTransform()->SetScale(Vec3(0.1f));

	_wolf->AddComponent(std::make_shared<ModelRenderer>(_shader));
	{
		_wolf->GetModelRenderer()->SetModel(model);
	}
}

void ImGuiDemo_TSoD::CreateTower()
{
	std::shared_ptr<Model> model = std::make_shared<Model>();
	model->ReadModel(L"Tower/Tower");
	model->ReadMaterial(L"Tower/Tower");

	_tower = std::make_shared<SceneObject>();
	_tower->GetOrAddTransform()->SetPosition(Vec3(0, 0, 50));
	_tower->GetOrAddTransform()->SetScale(Vec3(0.1f));

	_tower->AddComponent(std::make_shared<ModelRenderer>(_shader));
	{
		_tower->GetModelRenderer()->SetModel(model);
	}
}

void ImGuiDemo_TSoD::CreateTank()
{
	std::shared_ptr<Model> model = std::make_shared<Model>();
	model->ReadModel(L"Tank/Tank");
	model->ReadMaterial(L"Tank/Tank");

	_tank = std::make_shared<SceneObject>();
	_tank->GetOrAddTransform()->SetPosition(Vec3(0, 0, 50));
	_tank->GetOrAddTransform()->SetScale(Vec3(5.f));

	_tank->AddComponent(std::make_shared<ModelRenderer>(_shader));
	{
		_tank->GetModelRenderer()->SetModel(model);
	}
}
