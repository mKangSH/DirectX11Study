#pragma once

#include "Engine/01.Graphics/Buffer/Geometry.h"

class GeometryHelper
{
public:
	static void CreateQuad(std::shared_ptr<Geometry<VertexColorData>> geometry, Color color);
};

