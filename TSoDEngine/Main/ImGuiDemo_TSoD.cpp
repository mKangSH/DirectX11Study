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
#include "../UI/AssetBrowser.h"
#include "../UI/DirectXScene.h"
#include "../UI/VisualSequenceGraph.h"

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

	std::shared_ptr<DirectXScene> dxScene = std::make_shared<DirectXScene>();
	_uiComponents.push_back(dxScene);

	std::shared_ptr<AssetBrowser> assetBrowser = std::make_shared<AssetBrowser>();
	_uiComponents.push_back(assetBrowser);

	std::shared_ptr<VisualSequenceGraph> vsg = std::make_shared<VisualSequenceGraph>();
	_uiComponents.push_back(vsg);
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

	switch (selected)
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
	CreateDockSpace();

	ConstructUI();

	for (auto uiComponent : _uiComponents)
	{
		uiComponent->Update();
		uiComponent->Render();
	}
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

void ImGuiDemo_TSoD::ConstructUI()
{
	// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
	if (show_demo_window)
	{
		ImGui::ShowDemoWindow(&show_demo_window);
	}

	// 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
	if (show_setting_window)
	{
		ImGui::Begin("Setting");

		ImGuiIO& io = ImGui::GetIO();
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);

		if (ImGui::TreeNode("Single-Select"))
		{
			if (ImGui::Selectable("Wolf", selected == 0))
			{
				selected = 0;
			}
			
			if (ImGui::Selectable("Tower", selected == 1))
			{
				selected = 1;
			}
			
			if (ImGui::Selectable("Tank", selected == 2))
			{
				selected = 2;
			}

			if (ImGui::Selectable("Sphere", selected == 3))
			{
				selected = 3;
			}

			if (ImGui::Selectable("Cube", selected == 4))
			{
				selected = 4;
			}
			ImGui::TreePop();
		}
		ImGui::End();
	}

	// 3. Show another simple window.
	if (show_detail_window)
	{
		ImGui::Begin("Detail Window");

		ImGuiIO& io = ImGui::GetIO();

		if (ImGui::TreeNode("Backend Flags"))
		{
			ImGui::BeginDisabled();
			ImGui::CheckboxFlags("io.BackendFlags: HasGamepad", &io.BackendFlags, ImGuiBackendFlags_HasGamepad);
			ImGui::CheckboxFlags("io.BackendFlags: HasMouseCursors", &io.BackendFlags, ImGuiBackendFlags_HasMouseCursors);
			ImGui::CheckboxFlags("io.BackendFlags: HasSetMousePos", &io.BackendFlags, ImGuiBackendFlags_HasSetMousePos);
			ImGui::CheckboxFlags("io.BackendFlags: PlatformHasViewports", &io.BackendFlags, ImGuiBackendFlags_PlatformHasViewports);
			ImGui::CheckboxFlags("io.BackendFlags: HasMouseHoveredViewport", &io.BackendFlags, ImGuiBackendFlags_HasMouseHoveredViewport);
			ImGui::CheckboxFlags("io.BackendFlags: RendererHasVtxOffset", &io.BackendFlags, ImGuiBackendFlags_RendererHasVtxOffset);
			ImGui::CheckboxFlags("io.BackendFlags: RendererHasViewports", &io.BackendFlags, ImGuiBackendFlags_RendererHasViewports);
			ImGui::EndDisabled();

			ImGui::TreePop();
			ImGui::Spacing();
		}

		ImGui::End();
	}
}

void ImGuiDemo_TSoD::CreateDockSpace()
{
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
	
	const ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(viewport->WorkPos);
	ImGui::SetNextWindowSize(viewport->WorkSize);
	ImGui::SetNextWindowViewport(viewport->ID);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
	window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
	window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
	window_flags |= ImGuiWindowFlags_NoBackground;

	bool p_open = true;
	ImGui::Begin("DockSpaceDemo", &p_open, window_flags);

	ImGui::PopStyleVar(2);
	ImGuiIO& io = ImGui::GetIO();

	ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_PassthruCentralNode;
	if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
	{
		ImGuiID dockspace_id = ImGui::GetID("DockSpace");
		ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
	}

	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("View"))
		{
			ImGui::MenuItem("Setting Window", NULL, &show_setting_window);
			ImGui::MenuItem("Show Demo Window", NULL, &show_demo_window);
			ImGui::MenuItem("Show Detail Window", NULL, &show_detail_window);
			ImGui::EndMenu();
		}

		ImGui::EndMenuBar();
	}

	ImGui::End();
}
