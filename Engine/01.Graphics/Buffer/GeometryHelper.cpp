#include "pch.h"
#include "GeometryHelper.h"

void GeometryHelper::CreateQuad(std::shared_ptr<Geometry<VertexColorData>> geometry, Color color)
{
	std::vector<VertexColorData> vertices;
	vertices.resize(4);

	vertices[0].position = Vec3{ -0.5f, -0.5f, 0.f };
	vertices[1].position = Vec3{ -0.5f, 0.5f, 0.f };
	vertices[2].position = Vec3{ 0.5f, -0.5f, 0.f };
	vertices[3].position = Vec3{ 0.5f, 0.5f, 0.f };

	vertices[0].color = color;
	vertices[1].color = color;
	vertices[2].color = color;
	vertices[3].color = color;
	geometry->SetVertices(vertices);

	std::vector<uint32> indices;
	indices.resize(6);
	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;
	indices[3] = 2;
	indices[4] = 1;
	indices[5] = 3;
	geometry->SetIndices(indices);
}
