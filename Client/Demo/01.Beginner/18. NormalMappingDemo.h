#pragma once
#include "Engine/00.Engine/IExecute.h"
#include "Engine/01.Graphics/Buffer/Geometry.h"

class NormalMappingDemo : public IExecute
{
public:
	void Init() override;
	void Update() override;
	void Render() override;

	std::shared_ptr<Shader> _shader;

	std::shared_ptr<class SceneObject> _object;
	std::shared_ptr<class SceneObject> _object2;
	std::shared_ptr<class SceneObject> _mainCamera;
};

