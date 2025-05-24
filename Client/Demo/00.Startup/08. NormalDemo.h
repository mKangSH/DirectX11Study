#pragma once
#include "Engine/00.Engine/IExecute.h"
#include "Engine/01.Graphics/Buffer/Geometry.h"

class NormalDemo : public IExecute
{
public:
	void Init() override;
	void Update() override;
	void Render() override;

	std::shared_ptr<Shader> _shader;

	// Rasterizer
	RasterizerType _rasterizerType = RasterizerType::SOLID;

	// Object
	std::shared_ptr<Geometry<VertexTextureNormalData>> _geometry;
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

	// HeightMap
	std::shared_ptr<class Texture> _heightMap;
	ComPtr<ID3DX11EffectShaderResourceVariable> _heightMapVariable;

	ComPtr<ID3DX11EffectVectorVariable> _lightDirectionVariable;

	Vec3 _lightDirection = Vec3(-1.0f, -1.0f, 0.0f);
};

