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

	virtual void Update() override;

public:
	void SetMesh(std::shared_ptr<Mesh> mesh) { _mesh = mesh; }
	void SetMaterial(std::shared_ptr<Material> material) { _material = material; }

	// Legacy
	void SetShader(std::shared_ptr<Shader> shader) { }
	void SetTexture(std::shared_ptr<Texture> texture) { }
	void SetTechnique(uint8 value) { _technique = value; }
	void SetPass(uint8 value) { _pass = value; }

private:
	// Mesh
	std::shared_ptr<Mesh> _mesh = nullptr;
	std::shared_ptr<Material> _material = nullptr;

	uint8 _technique = 2;
	uint8 _pass = 255;

	// std::shared_ptr<Shader> _shader = nullptr;
	// std::shared_ptr<Texture> _texture = nullptr;

	// ComPtr<ID3DX11EffectShaderResourceVariable> _textureVariable;
};

