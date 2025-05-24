#pragma once

class ImGuiDemo_Window : public IExecute
{
public:
	void Init() override;
	void Update() override;
	void Render() override;
	void ImGuiRender() override;

	void CreateWolf();
	void CreateTower();
	void CreateTank();

	void ConstructUI();

	void CreateDX11Scene();
	void CreateDockSpace();
	
private:
	std::shared_ptr<Shader> _shader;
	std::shared_ptr<SceneObject> _wolf;
	std::shared_ptr<SceneObject> _tower;
	std::shared_ptr<SceneObject> _tank;
	std::shared_ptr<SceneObject> _sphere;
	std::shared_ptr<SceneObject> _cube;
	std::shared_ptr<SceneObject> _mainCamera;

	bool show_setting_window = true;
	bool show_demo_window = false;
	bool show_detail_window = false;

	int selected = -1;

	Vec4 clear_color = Vec4(0.f);
};

