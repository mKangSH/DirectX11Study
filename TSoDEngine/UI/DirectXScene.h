#pragma once
#include "UIComponentBase.h"

class DirectXScene : public UIComponentBase
{
	using Super = UIComponentBase;

public:
	DirectXScene();
	virtual ~DirectXScene();

	virtual void Update() override;
	virtual void Render() override;

private:
	void Draw();

private:
	int _rasterizerState = 0;
	int _topology = 0;

	const char* _rasterizerType[4] = { "SOLID", "WIREFRAME", "SOLID_RED", "WIREFRAME_RED"};
	const char* _primitiveType[2] = { "AUTO", "POINT LIST"};
};

