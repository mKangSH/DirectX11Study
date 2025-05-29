#pragma once

struct GameDesc
{
	std::shared_ptr<class IExecute> app = nullptr;
	std::wstring appName = L"";
	HINSTANCE hInstance = nullptr;
	HWND hWnd = nullptr;
	float width = 1920.0f;
	float height = 1080.0f;
	bool vsync = false;
	bool windowed = true;
	Vec4 clearColor = Vec4(0.0f, 0.0f, 0.0f, 255.0f);
};

class Game
{
	DECLARE_SINGLETON(Game)

public:
	WPARAM Run(GameDesc& desc);

	GameDesc& GetGameDesc() { return _desc; }

private:
	ATOM MyRegisterClass();
	BOOL InitInstance(int cmdShow);

	void Update();

	static LRESULT CALLBACK WndProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);

private:
	GameDesc _desc;
};

