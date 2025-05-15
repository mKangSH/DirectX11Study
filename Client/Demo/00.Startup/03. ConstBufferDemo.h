#pragma once
#include "Engine/00.Engine/IExecute.h"
#include "Engine/01.Graphics/Buffer/Geometry.h"

enum class RasterizerType
{
	SOLID,
	WIREFRAME,
};

class ConstBufferDemo : public IExecute
{
public:
	void Init() override;
	void Update() override;
	void Render() override;

	std::shared_ptr<Shader> _shader;

	std::shared_ptr<Geometry<VertexColorData>> _geometry;
	std::shared_ptr<VertexBuffer> _vertexBuffer;
	std::shared_ptr<IndexBuffer> _indexBuffer;

	Vec3 _translation = Vec3(0.f, 0.f, 0.f);

	Matrix _world = Matrix::Identity;
	Matrix _view = Matrix::Identity;
	Matrix _projection = Matrix::Identity;

	RasterizerType _rasterizerType = RasterizerType::SOLID;

	ComPtr<ID3DX11EffectMatrixVariable> _worldVariable;
	ComPtr<ID3DX11EffectMatrixVariable> _viewVariable;
	ComPtr<ID3DX11EffectMatrixVariable> _projectionVariable;
};

