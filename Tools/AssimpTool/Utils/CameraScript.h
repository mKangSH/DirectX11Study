#pragma once

#include "Engine/04.Component/MonoBehaviour.h"

class CameraScript : public MonoBehaviour
{
	using Super = MonoBehaviour;

public:
	CameraScript();
	virtual ~CameraScript();

	virtual void Start() override;
	virtual void Update() override;

private:
	void KeyboardScript(const float& deltaTime);
	void MouseScript(const float& deltaTime);

private:
	float _speed = 10.0f;
	POINT _prevMousePos = { 0, 0 };

	std::shared_ptr<Transform> _cameraTransform = nullptr;
};

