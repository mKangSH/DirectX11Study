#include "pch.h"
#include "Main.h"
#include "Engine/02.Managers/Game.h"
#include "../Game/04. CameraDemo.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	GameDesc desc;
	desc.appName = L"GameCoding";
	desc.hInstance = hInstance;
	desc.vsync = false;
	desc.hWnd = NULL;
	desc.width = 1920;
	desc.height = 1080;
	desc.clearColor = DirectX::Colors::Black;
	desc.app = std::make_shared<CameraDemo>();

	GAME->Run(desc);

	return 0;
}