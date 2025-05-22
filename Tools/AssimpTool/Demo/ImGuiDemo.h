#pragma once

class ImGuiDemo : public IExecute
{
public:
	void Init() override;
	void Update() override;
	void Render() override;

	void CreateWolf();
	void CreateTower();
	void CreateTank();

	void Test();

	void CreateDockSpace();

private:
	std::shared_ptr<Shader> _shader;
	std::shared_ptr<SceneObject> _object;
	std::shared_ptr<SceneObject> _mainCamera;

	bool show_setting_window = false;
	bool show_demo_window = false;
	bool show_detail_window = false;

	Vec4 clear_color = Vec4(0.f);
};

