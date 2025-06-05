#include "pch.h"
#include "DataAnalysisGraph3D.h"

DataAnalysisGraph3D::DataAnalysisGraph3D() : Super()
{
	_title = "Data Analysis Graph 3D";
}

DataAnalysisGraph3D::~DataAnalysisGraph3D()
{
}

void DataAnalysisGraph3D::Update()
{
	if (_isVisible)
	{
		Draw();
	}
}

void DataAnalysisGraph3D::Render()
{

}

void DataAnalysisGraph3D::Draw()
{
	ImPlot3D::ShowDemoWindow(&_isVisible);
}