#include "pch.h"
#include "DirectXScene.h"

DirectXScene::DirectXScene() : Super()
{
	_title = "DirectX Scene";
}

DirectXScene::~DirectXScene()
{
}

void DirectXScene::Update()
{
	if (_isVisible)
	{
		Draw();
	}
}

void DirectXScene::Render()
{

}

void DirectXScene::Draw()
{
	ImGuiColorEditFlags base_flags = ImGuiColorEditFlags_None;

	D3D11_PRIMITIVE_TOPOLOGY topology;
	DEVICECONTEXT->IAGetPrimitiveTopology(&topology);

	_topology = topology;
	_rasterizerState = static_cast<int>(RENDER->GetRasterizerState());

	ImGui::Begin("DirectX Scene", &_isVisible, ImGuiWindowFlags_MenuBar);

	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginTable("Scene Tool Bar", 7))
		{
			ImGui::TableNextColumn();
			ImGui::Combo("Rasterizer", &_rasterizerState, _rasterizerType, IM_ARRAYSIZE(_rasterizerType));

			ImGui::TableNextColumn();
			ImGui::TableNextColumn();

			ImGui::Combo("Topology", &_topology, _primitiveType, IM_ARRAYSIZE(_primitiveType));

			ImGui::TableNextColumn();
			ImGui::TableNextColumn();
			
			ImGui::TableNextColumn();
			ImGui::TableNextColumn();

			ImGui::Text("Background Color");
			ImGui::ColorEdit4("BG Color Picker", (float*)(&GAME->GetGameDesc().clearColor), ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | base_flags);
			ImGui::EndTable();
		}

		ImGui::EndMenuBar();
	}
	
	ImVec2 size = ImGui::GetContentRegionAvail();
	if ((size.x != GRAPHICS->GetSceneTextureWidth()) || (size.y != GRAPHICS->GetSceneTextureHeight()))
	{
		// Resize the ImGui window to match the game window size
		if(size.x < GAME->GetGameDesc().width && size.y < GAME->GetGameDesc().height)
		{
			GRAPHICS->SetSceneTextureSize(static_cast<UINT>(size.x), static_cast<UINT>(size.y));
		}
	}

	DEVICECONTEXT->IASetPrimitiveTopology(static_cast<D3D11_PRIMITIVE_TOPOLOGY>(_topology));
	RENDER->SetRasterizerState(static_cast<RasterizerType>(_rasterizerState));

	ComPtr<ID3D11ShaderResourceView> test = GRAPHICS->GetShaderResourceView();

	ImGui::Image((ImTextureID)test.Get(), size);

	ImGui::End();
}