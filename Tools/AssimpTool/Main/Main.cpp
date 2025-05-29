#include "pch.h"
#include "Main.h"
#include "../Demo/AssimpTool.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	GameDesc desc;
	desc.appName = L"Dx11 Renderer";
	desc.hInstance = hInstance;
	desc.vsync = false;
	desc.hWnd = NULL;
	desc.width = 1920;
	desc.height = 1080;
	desc.clearColor = DirectX::Colors::Black;
	desc.app = std::make_shared<AssimpTool>();

	GAME->Run(desc);

	return 0;
}