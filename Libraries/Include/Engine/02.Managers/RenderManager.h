#pragma once

#include "../01.Graphics/Buffer/ConstantBuffer.h"

struct GlobalDesc
{
	Matrix View = Matrix::Identity;
	Matrix Projection = Matrix::Identity;
	Matrix ViewProjection = Matrix::Identity;
};

enum class RasterizerType
{
	SOLID,
	WIREFRAME,
};

struct TransformDesc
{
	Matrix World = Matrix::Identity;
};

class RenderManager
{
	DECLARE_SINGLETON(RenderManager)

public:
	void Init(std::shared_ptr<Shader> shader);
	void Update();

	void UploadGlobalDesc(const Matrix& view, const Matrix& projection);
	void UploadTransformDesc(const TransformDesc& desc);

public:
	void SetRasterizerState(RasterizerType type) { _rasterizerType = type; }

	RasterizerType GetRasterizerState() const { return _rasterizerType; }

private:
	std::shared_ptr<Shader> _shader = nullptr;

	GlobalDesc _globalDesc = {};
	std::shared_ptr<ConstantBuffer<GlobalDesc>> _globalBuffer = nullptr;
	ComPtr<ID3DX11EffectConstantBuffer> _globalEffectBuffer = nullptr;

	TransformDesc _transformDesc = {};
	std::shared_ptr<ConstantBuffer<TransformDesc>> _transformBuffer = nullptr;
	ComPtr<ID3DX11EffectConstantBuffer> _transformEffectBuffer = nullptr;

	// Rasterizer
	RasterizerType _rasterizerType = RasterizerType::SOLID;
};

