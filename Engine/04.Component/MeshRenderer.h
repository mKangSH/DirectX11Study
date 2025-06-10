#pragma once
#include "Component.h"

class Mesh;
class Shader;
class Material;

class MeshRenderer : public Component
{
	using Super = Component;

public:
	MeshRenderer();
	virtual ~MeshRenderer();

public:
	void RenderInstancing(std::shared_ptr<class InstancingBuffer>& buffer);

public:
	void SetMesh(std::shared_ptr<Mesh> mesh) { _mesh = mesh; }
	void SetMaterial(std::shared_ptr<Material> material) { _material = material; }
	void SetPass(uint8 pass) { _pass = pass; }

	const InstanceID GetInstanceID() const;

private:
	// Mesh
	std::shared_ptr<Mesh> _mesh = nullptr;
	std::shared_ptr<Material> _material = nullptr;
	uint8 _pass = 0;
};

