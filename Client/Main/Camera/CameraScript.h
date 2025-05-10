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
	float _speed = 10.0f;
};

