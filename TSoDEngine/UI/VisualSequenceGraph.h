#pragma once
#include "UIComponentBase.h"

struct LinkInfo
{
	ax::NodeEditor::LinkId Id;
	ax::NodeEditor::PinId  InputId;
	ax::NodeEditor::PinId  OutputId;
};

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

	ax::NodeEditor::EditorContext* _editorContext = nullptr;

	ImVector<LinkInfo>   m_Links;
	int                  m_NextLinkId = 100;
};

