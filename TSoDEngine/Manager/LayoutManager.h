#pragma once

class UIComponentBase;

class LayoutManager
{
public:
	void Init();
	void Update();
	void Render();

	void ConstructUI();

public:
	std::vector<std::shared_ptr<UIComponentBase>> GetUIComponents() const { return _uiComponents; }
	int GetSelected() const { return selected; }

private:
	std::vector<std::shared_ptr<UIComponentBase>> _uiComponents;

	bool show_setting_window = true;
	bool show_demo_window = true;
	bool show_detail_window = false;

	int selected = -1;
};

