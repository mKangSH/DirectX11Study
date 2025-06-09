#pragma once

class ImGuiDemo_TSoD : public IExecute
{
public:
	void Init() override;
	void Update() override;
	void Render() override;
	void ImGuiRender() override;

	void CreateWolf();
	void CreateTower();
	void CreateTank();
	void CreateKachujin();
	
private:
	std::shared_ptr<Shader> _shader;
	std::shared_ptr<SceneObject> _wolf;
	std::shared_ptr<SceneObject> _tower;
	std::shared_ptr<SceneObject> _tank;
	std::shared_ptr<SceneObject> _sphere;
	std::shared_ptr<SceneObject> _kachujin;
	std::shared_ptr<SceneObject> _cube;
	std::shared_ptr<SceneObject> _sky;
	std::shared_ptr<SceneObject> _mainCamera;

	std::shared_ptr<class LayoutManager> _layoutManager = nullptr;

	Vec4 clear_color = Vec4(0.f);
};

