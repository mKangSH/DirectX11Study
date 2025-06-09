#pragma once

class InstancingDemo : public IExecute
{
public:
	void Init() override;
	void Update() override;
	void Render() override;

private:
	std::shared_ptr<Shader> _shader;
	std::shared_ptr<SceneObject> _mainCamera;
	std::vector<std::shared_ptr<SceneObject>> _objects;

private:
	std::shared_ptr<Mesh> _mesh;
	std::shared_ptr<Material> _material;

	std::vector<Matrix> _worldMatrices;
	std::shared_ptr<VertexBuffer> _instanceBuffer;
};

