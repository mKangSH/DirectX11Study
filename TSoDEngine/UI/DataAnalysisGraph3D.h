#pragma once
#include "UIComponentBase.h"

class DataAnalysisGraph3D : public UIComponentBase
{
	using Super = UIComponentBase;

public:
	DataAnalysisGraph3D();
	virtual ~DataAnalysisGraph3D();

	virtual void Update() override;
	virtual void Render() override;

private:
	void Draw();
};

