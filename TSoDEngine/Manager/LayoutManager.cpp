#include "pch.h"
#include "LayoutManager.h"
#include "../UI/UIComponentBase.h"
#include "../UI/AssetBrowser.h"
#include "../UI/DirectXScene.h"
#include "../UI/VisualSequenceGraph.h"
#include "../UI/GraphingCanvas.h"

void LayoutManager::Init()
{
	std::shared_ptr<DirectXScene> dxScene = std::make_shared<DirectXScene>();
	_uiComponents.push_back(dxScene);

	std::shared_ptr<AssetBrowser> assetBrowser = std::make_shared<AssetBrowser>();
	_uiComponents.push_back(assetBrowser);

	std::shared_ptr<VisualSequenceGraph> vsg = std::make_shared<VisualSequenceGraph>();
	_uiComponents.push_back(vsg);

	std::shared_ptr<GraphingCanvas> graphingCanvas = std::make_shared<GraphingCanvas>();
	_uiComponents.push_back(graphingCanvas);
}

void LayoutManager::Update()
{
	ImGui::DockSpaceOverViewport();

	ConstructUI();

	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("View"))
		{
			ImGui::MenuItem("Demo Window", "", &show_demo_window);
			ImGui::Separator();

			for (auto uiComponent : _uiComponents)
			{
				ImGui::MenuItem(uiComponent->GetTitle().c_str(), "", uiComponent->IsVisible());
			}

			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}

	for (auto uiComponent : _uiComponents)
	{
		uiComponent->Update();
	}
}

void LayoutManager::Render()
{
	for (auto uiComponent : _uiComponents)
	{
		uiComponent->Render();
	}
}

void LayoutManager::ConstructUI()
{
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

