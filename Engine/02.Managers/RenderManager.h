#pragma once

#include "../01.Graphics/Buffer/ConstantBuffer.h"

struct GlobalDesc
{
	Matrix View = Matrix::Identity;
	Matrix Projection = Matrix::Identity;
	Matrix ViewProjection = Matrix::Identity;
	Matrix ViewInverse = Matrix::Identity;
};

struct TransformDesc
{
	Matrix World = Matrix::Identity;
};

// Light
struct LightDesc
{
	Vec4 ambient = Vec4(1.0f, 1.0f, 1.0f, 1.0f);
	Vec4 diffuse = Vec4(1.0f, 1.0f, 1.0f, 1.0f);
	Vec4 specular = Vec4(1.0f, 1.0f, 1.0f, 1.0f);
	Vec4 emissive = Vec4(1.0f, 1.0f, 1.0f, 1.0f);

	Vec3 direction;
	float padding0;
};

struct MaterialDesc
{
	Vec4 ambient = Vec4(0.0f, 0.0f, 0.0f, 1.0f);
	Vec4 diffuse = Vec4(1.0f, 1.0f, 1.0f, 1.0f);
	Vec4 specular = Vec4(0.0f, 0.0f, 0.0f, 1.0f);
	Vec4 emissive = Vec4(0.0f, 0.0f, 0.0f, 1.0f);
};

#define MAX_BONE_TRANSFORMS 50

struct BoneDesc
{
	Matrix transforms[MAX_BONE_TRANSFORMS];

	BoneDesc()
	{
		std::fill(std::begin(transforms), std::end(transforms), Matrix::Identity);
	}
};

enum class RasterizerType
{
	SOLID,
	WIREFRAME,
};

class RenderManager
{
	DECLARE_SINGLETON(RenderManager)

public:
	void Init(std::shared_ptr<Shader> shader);
	void Update();

	void UploadGlobalDesc(const Matrix& view, const Matrix& projection);
	void UploadTransformDesc(const TransformDesc& desc);
	void UploadLightDesc(const LightDesc& desc);
	void UploadMaterialDesc(const MaterialDesc& desc);
	void UploadBoneDesc(const BoneDesc& desc);

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

	LightDesc _lightDesc = {};
	std::shared_ptr<ConstantBuffer<LightDesc>> _lightBuffer = nullptr;
	ComPtr<ID3DX11EffectConstantBuffer> _lightEffectBuffer = nullptr;

	MaterialDesc _materialDesc = {};
	std::shared_ptr<ConstantBuffer<MaterialDesc>> _materialBuffer = nullptr;
	ComPtr<ID3DX11EffectConstantBuffer> _materialEffectBuffer = nullptr;

	BoneDesc _boneDesc = {};
	std::shared_ptr<ConstantBuffer<BoneDesc>> _boneBuffer = nullptr;
	ComPtr< ID3DX11EffectConstantBuffer> _boneEffectBuffer = nullptr;
};

