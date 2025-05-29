#pragma once
#include "UIComponentBase.h"

class GraphingCanvas : public UIComponentBase
{
	using Super = UIComponentBase;

public:
	GraphingCanvas();
	virtual ~GraphingCanvas();

public:
	void Update() override;
	void Render() override;

private:
	void Draw();

	float _alpha = 1.0f;
};

