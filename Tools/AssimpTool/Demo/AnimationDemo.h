#pragma once

class AnimationDemo : public IExecute
{
public:
	void Init() override;
	void Update() override;
	void Render() override;

	void CreateKachujin();
	void CreateWolf();
	void CreateTower();
	void CreateTank();

private:
	std::shared_ptr<Shader> _shader;
	std::shared_ptr<SceneObject> _object;
	std::shared_ptr<SceneObject> _mainCamera;
};

