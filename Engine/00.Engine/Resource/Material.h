#pragma once
#include "ResourceBase.h"

class Material : public ResourceBase
{
	using Super = ResourceBase;

public:
	Material();
	virtual ~Material();

	std::shared_ptr<Shader> GetShader() const { return _shader; }

	MaterialDesc& GetMaterialDesc() { return _desc; }

	const std::shared_ptr<Texture>& GetDiffuseMap() const { return _diffuseMap; }
	const std::shared_ptr<Texture>& GetNormalMap() const { return _normalMap; }
	const std::shared_ptr<Texture>& GetSpecularMap() const { return _specularMap; }
	const std::shared_ptr<Texture>& GetEmissiveMap() const { return _emissiveMap; }

	void SetShader(std::shared_ptr<Shader> shader);
	void SetDiffuseMap(std::shared_ptr<Texture> diffuseMap) { _diffuseMap = diffuseMap; }
	void SetNormalMap(std::shared_ptr<Texture> normalMap) { _normalMap = normalMap; }
	void SetSpecularMap(std::shared_ptr<Texture> specularMap) { _specularMap = specularMap; }
	void SetEmissiveMap(std::shared_ptr<Texture> emissiveMap) { _emissiveMap = emissiveMap; }

	void Update();

	std::shared_ptr<Material> Clone();

private:
	friend class MeshRenderer;

	MaterialDesc _desc;

private:
	std::shared_ptr<Shader> _shader;
	std::shared_ptr<Texture> _diffuseMap;
	std::shared_ptr<Texture> _normalMap;
	std::shared_ptr<Texture> _specularMap;
	std::shared_ptr<Texture> _emissiveMap;

	ComPtr<ID3DX11EffectShaderResourceVariable> _diffuseEffectVariable;
	ComPtr<ID3DX11EffectShaderResourceVariable> _normalEffectVariable;
	ComPtr<ID3DX11EffectShaderResourceVariable> _specularEffectVariable;
	ComPtr<ID3DX11EffectShaderResourceVariable> _emissiveEffectVariable;
};

