#pragma once
#include "Component.h"

class Mesh;
class Shader;

class MeshRenderer : public Component
{
	using Super = Component;

public:
	MeshRenderer();
	virtual ~MeshRenderer();

	virtual void Update() override;

public:
	void SetMesh(std::shared_ptr<Mesh> mesh) { _mesh = mesh; }
	void SetShader(std::shared_ptr<Shader> shader);
	void SetTexture(std::shared_ptr<Texture> texture) { _texture = texture; }

private:
	// Mesh
	std::shared_ptr<Mesh> _mesh = nullptr;
	std::shared_ptr<Shader> _shader = nullptr;
	std::shared_ptr<Texture> _texture = nullptr;

	ComPtr<ID3DX11EffectMatrixVariable> _worldVariable;
	ComPtr<ID3DX11EffectMatrixVariable> _viewVariable;
	ComPtr<ID3DX11EffectMatrixVariable> _projectionVariable;
	ComPtr<ID3DX11EffectShaderResourceVariable> _textureVariable;
};

