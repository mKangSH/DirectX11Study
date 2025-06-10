#pragma once

class MeshInstancingDemo : public IExecute
{
public:
	void Init() override;
	void Update() override;
	void Render() override;

private:
	std::shared_ptr<Shader> _shader;
	std::shared_ptr<SceneObject> _mainCamera;
	std::vector<std::shared_ptr<SceneObject>> _objects;
};

