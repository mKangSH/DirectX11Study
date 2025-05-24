#pragma once
#include "Engine/00.Engine/IExecute.h"
#include "Engine/01.Graphics/Buffer/Geometry.h"

class GlobalTestDemo : public IExecute
{
public:
	void Init() override;
	void Update() override;
	void Render() override;

	// Rasterizer
	RasterizerType _rasterizerType = RasterizerType::SOLID;

	std::shared_ptr<Shader> _shader;

	std::shared_ptr<class SceneObject> _object;
	std::shared_ptr<class SceneObject> _mainCamera;

	ComPtr<ID3DX11EffectVectorVariable> _lightDirectionVariable;
	Vec3 _lightDirection = Vec3(-1.0f, -1.0f, 0.0f);
};

