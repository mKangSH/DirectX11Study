#pragma once

#include "Engine/01.Graphics/Buffer/Geometry.h"

class GeometryHelper
{
	// 사각형 + 큐브 + 구 + 그리드 + 실린더
public:
	static void CreateQuad(std::shared_ptr<Geometry<VertexColorData>> geometry, Color color);

	static void CreateQuad(std::shared_ptr<Geometry<VertexTextureData>> geometry);
	static void CreateCube(std::shared_ptr<Geometry<VertexTextureData>> geometry);
	static void CreateSphere(std::shared_ptr<Geometry<VertexTextureData>> geometry);
	static void CreateGrid(std::shared_ptr<Geometry<VertexTextureData>> geometry, int32 sizeX, int32 sizeZ);
};

