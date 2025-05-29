#include "pch.h"
#include "GraphingCanvas.h"

GraphingCanvas::GraphingCanvas()
{
	_title = "Graphing Canvas";
}

GraphingCanvas::~GraphingCanvas()
{
}

void GraphingCanvas::Update()
{
	if (_isVisible)
	{
		Draw();
	}
}

void GraphingCanvas::Render()
{

}

void GraphingCanvas::Draw()
{
	ImPlot::ShowDemoWindow(&_isVisible);
}