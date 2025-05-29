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
	int _rasterizerState;
	int _topology;
};

