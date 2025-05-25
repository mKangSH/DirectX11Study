#pragma once

class ImGuiManager
{
	DECLARE_SINGLETON(ImGuiManager)

public:
	void Init();
	void Update();
	void Render();

};

