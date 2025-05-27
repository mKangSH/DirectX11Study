#pragma once
#include "UIComponentBase.h"

class VisualSequenceGraph : public UIComponentBase
{
	using Super = UIComponentBase;

public:
	VisualSequenceGraph();
	virtual ~VisualSequenceGraph();

public:
	void Update() override;
	void Render() override;

private:
	void Draw();

private:
	ImVector<ImVec2> _points;
	ImVec2 _scrolling = ImVec2(0.0f, 0.0f);
	bool _optEnableGrid = true;
	bool _optEnableContextMenu = true;
	bool _addingLine = false;
};

