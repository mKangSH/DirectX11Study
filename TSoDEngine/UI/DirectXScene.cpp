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
	ImGui::Begin("DirectX Scene", &_isVisible);

	ImVec2 size = ImGui::GetContentRegionAvail();
	if ((size.x != GRAPHICS->GetSceneTextureWidth()) || (size.y != GRAPHICS->GetSceneTextureHeight()))
	{
		// Resize the ImGui window to match the game window size
		if(size.x < GAME->GetGameDesc().width && size.y < GAME->GetGameDesc().height)
		{
			GRAPHICS->SetSceneTextureSize(static_cast<UINT>(size.x), static_cast<UINT>(size.y));
		}
	}

	if (ImGui::IsWindowFocused())
	{
		ImGuiIO& io = ImGui::GetIO();

		ImGuiKey start_key = ImGuiKey_NamedKey_BEGIN;
		for (ImGuiKey key = start_key; key < ImGuiKey_NamedKey_END; key = (ImGuiKey)(key + 1))
		{
			if (ImGui::IsKeyPressed(key) == false)
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

	ImGui::Image((ImTextureID)test.Get(), size);

	ImGui::End();
}