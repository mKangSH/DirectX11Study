#include "pch.h"
#include "ImGuiDemo.h"
#include "Engine/00.Engine/Resource/ResourceBase.h"
#include "Engine/00.Engine/Resource/Texture.h"
#include "Engine/00.Engine/Resource/Mesh.h"
#include "Engine/00.Engine/Resource/Material.h"
#include "Engine/00.Engine/Resource/Model/Model.h"
#include "Engine/03.SceneObject/SceneObject.h"
#include "Engine/04.Component/Camera.h"
#include "Engine/04.Component/MeshRenderer.h"
#include "Engine/04.Component/ModelRenderer.h"
#include "../Utils/CameraScript.h"

void ImGuiDemo::Init()
{
	RESOURCES->Init(L"..\\Resources\\");
	_shader = std::make_shared<Shader>(L"02.Intermediate\\15. ModelDemo.fx");
	RENDER->Init(_shader);

	// Camera
	_mainCamera = std::make_shared<SceneObject>();
	_mainCamera->GetOrAddTransform()->SetPosition(Vec3(0.0f, 0.0f, -5.0f));
	std::shared_ptr<Camera> perspectiveCamera = std::make_shared<Camera>();
	_mainCamera->AddComponent(perspectiveCamera);
	_mainCamera->AddComponent(std::make_shared<CameraScript>());

	_mainCamera->Start();

	// Object
	CreateTank();
}

void ImGuiDemo::Update()
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

	Test();
}

void ImGuiDemo::Render()
{
}

void ImGuiDemo::CreateWolf()
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
		_object->GetModelRenderer()->SetPass(3);
	}
}

void ImGuiDemo::CreateTower()
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

void ImGuiDemo::CreateTank()
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

void ImGuiDemo::Test()
{
	// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
	if (show_demo_window)
	{
		ImGui::ShowDemoWindow(&show_demo_window);
	}

	CreateDockSpace();

	// 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
	if (show_setting_window)
	{
		static float f = 0.0f;
		static int counter = 0;

		ImGui::Begin("Setting");

		ImGui::Text("This is some useful text.");

		ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
		ImGui::ColorEdit3("clear color", (float*)&clear_color);

		if (ImGui::Button("Button"))
		{
			counter++;
		}

		ImGui::SameLine();
		ImGui::Text("counter = %d", counter);

		ImGuiIO& io = ImGui::GetIO();
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
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

void ImGuiDemo::CreateDockSpace()
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
