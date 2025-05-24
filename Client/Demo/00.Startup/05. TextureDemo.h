#pragma once
#include "Engine/00.Engine/IExecute.h"
#include "Engine/01.Graphics/Buffer/Geometry.h"

class TextureDemo : public IExecute
{
public:
	void Init() override;
	void Update() override;
	void Render() override;

	std::shared_ptr<Shader> _shader;

	// Rasterizer
	RasterizerType _rasterizerType = RasterizerType::SOLID;

	// Object
	std::shared_ptr<Geometry<VertexTextureData>> _geometry;
	std::shared_ptr<VertexBuffer> _vertexBuffer;
	std::shared_ptr<IndexBuffer> _indexBuffer;

	Matrix _world = Matrix::Identity;

	ComPtr<ID3DX11EffectMatrixVariable> _worldVariable;
	ComPtr<ID3DX11EffectMatrixVariable> _viewVariable;
	ComPtr<ID3DX11EffectMatrixVariable> _projectionVariable;

	// Camera
	std::shared_ptr<class SceneObject> _mainCamera;

	// Texture
	std::shared_ptr<class Texture> _texture;
	ComPtr<ID3DX11EffectShaderResourceVariable> _textureVariable;
};

