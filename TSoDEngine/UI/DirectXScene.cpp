#include "pch.h"
#include "DirectXScene.h"

DirectXScene::DirectXScene()
{
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
	ImGui::Begin("Dx11 Scene");

	ImVec2 sceneRegionMin = ImGui::GetWindowContentRegionMin();
	ImVec2 sceneRegionMax = ImGui::GetWindowContentRegionMax();

	if ((sceneRegionMax.x - sceneRegionMin.x != GAME->GetGameDesc().width) &&
		(sceneRegionMax.y - sceneRegionMin.y != GAME->GetGameDesc().height))
	{
		// Resize the ImGui window to match the game window size
	}

	if (ImGui::IsWindowFocused())
	{
		ImGuiIO& io = ImGui::GetIO();

		ImGuiKey start_key = ImGuiKey_NamedKey_BEGIN;
		struct funcs
		{
			static bool IsLegacyNativeDupe(ImGuiKey)
			{
				return false;
			}
		};

		for (ImGuiKey key = start_key; key < ImGuiKey_NamedKey_END; key = (ImGuiKey)(key + 1))
		{
			if (funcs::IsLegacyNativeDupe(key) || ImGui::IsKeyPressed(key) == false)
			{
				continue;
			}

			if (key == ImGuiKey::ImGuiKey_Tab)
			{
				if (RENDER->GetRasterizerState() == RasterizerType::SOLID)
				{
					RENDER->SetRasterizerState(RasterizerType::WIREFRAME);
				}
				else if (RENDER->GetRasterizerState() == RasterizerType::WIREFRAME)
				{
					RENDER->SetRasterizerState(RasterizerType::SOLID_RED);
				}
				else if (RENDER->GetRasterizerState() == RasterizerType::SOLID_RED)
				{
					RENDER->SetRasterizerState(RasterizerType::WIREFRAME_RED);
				}
				else if (RENDER->GetRasterizerState() == RasterizerType::WIREFRAME_RED)
				{
					RENDER->SetRasterizerState(RasterizerType::SOLID);
				}
			}

			if (key == ImGuiKey::ImGuiKey_LeftShift)
			{
				D3D11_PRIMITIVE_TOPOLOGY topology;
				DEVICECONTEXT->IAGetPrimitiveTopology(&topology);
				if (topology == D3D11_PRIMITIVE_TOPOLOGY::D3D_PRIMITIVE_TOPOLOGY_UNDEFINED)
				{
					topology = D3D11_PRIMITIVE_TOPOLOGY_POINTLIST;
				}
				else if (topology == D3D11_PRIMITIVE_TOPOLOGY_POINTLIST)
				{
					topology = D3D11_PRIMITIVE_TOPOLOGY::D3D_PRIMITIVE_TOPOLOGY_UNDEFINED;
				}
				DEVICECONTEXT->IASetPrimitiveTopology(topology);
			}
		}
	}

	ComPtr<ID3D11ShaderResourceView> test = GRAPHICS->GetShaderResourceView();

	ImGui::Image((ImTextureID)test.Get(), ImVec2(GAME->GetGameDesc().width, GAME->GetGameDesc().height));

	ImGui::End();
}