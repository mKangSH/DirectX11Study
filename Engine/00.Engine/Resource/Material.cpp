#include "pch.h"
#include "Material.h"
#include "Texture.h"

Material::Material() : Super(ResourceType::Material)
{
}

Material::~Material()
{
}

void Material::SetShader(std::shared_ptr<Shader> shader)
{
	_shader = shader;

	_diffuseEffectVariable = _shader->GetSRV("DiffuseMap");
	_normalEffectVariable = _shader->GetSRV("NormalMap");
	_specularEffectVariable = _shader->GetSRV("SpecularMap");
}

void Material::Update()
{
	if (_shader == nullptr)
	{
		return;
	}

	RENDER->UploadMaterialDesc(_desc);

	if (_diffuseMap)
	{
		_diffuseEffectVariable->SetResource(_diffuseMap->GetShaderResourceView().Get());
	}

	if (_normalMap)
	{
		_normalEffectVariable->SetResource(_normalMap->GetShaderResourceView().Get());
	}

	if (_specularMap)
	{
		_specularEffectVariable->SetResource(_specularMap->GetShaderResourceView().Get());
	}
}

std::shared_ptr<Material> Material::Clone()
{
	std::shared_ptr<Material> material = std::make_shared<Material>();

	material->_desc = _desc;
	material->_shader = _shader;
	material->_diffuseMap = _diffuseMap;
	material->_normalMap = _normalMap;
	material->_specularMap = _specularMap;
	material->_emissiveMap = _emissiveMap;
	material->_diffuseEffectVariable = _diffuseEffectVariable;
	material->_normalEffectVariable = _normalEffectVariable;
	material->_specularEffectVariable = _specularEffectVariable;
	material->_emissiveEffectVariable = _emissiveEffectVariable;

	return material;
}
