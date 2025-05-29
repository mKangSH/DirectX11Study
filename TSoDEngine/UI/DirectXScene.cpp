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
		if (ImGui::BeginTable("Scene Tool Bar", 3))
		{
			ImGui::TableNextColumn();

			ImGui::RadioButton("SOLID", &_rasterizerState, static_cast<int>(RasterizerType::SOLID));
			ImGui::RadioButton("WIREFRAME", &_rasterizerState, static_cast<int>(RasterizerType::WIREFRAME));
			ImGui::RadioButton("SOLID_RED", &_rasterizerState, static_cast<int>(RasterizerType::SOLID_RED));
			ImGui::RadioButton("WIREFRAME_RED", &_rasterizerState, static_cast<int>(RasterizerType::WIREFRAME_RED));

			ImGui::TableNextColumn();

			ImGui::RadioButton("UNDEFINED", &_topology, D3D11_PRIMITIVE_TOPOLOGY::D3D_PRIMITIVE_TOPOLOGY_UNDEFINED);
			ImGui::RadioButton("POINTLIST", &_topology, D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
			
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