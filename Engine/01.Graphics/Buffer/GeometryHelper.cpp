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

void GeometryHelper::CreateQuad(std::shared_ptr<Geometry<VertexTextureData>> geometry)
{
	std::vector<VertexTextureData> vertices;
	vertices.resize(4);

	vertices[0].position = Vec3{ -0.5f, -0.5f, 0.f };
	vertices[1].position = Vec3{ -0.5f, 0.5f, 0.f };
	vertices[2].position = Vec3{ 0.5f, -0.5f, 0.f };
	vertices[3].position = Vec3{ 0.5f, 0.5f, 0.f };

	vertices[0].uv = Vec2{ 0.f, 1.f };
	vertices[1].uv = Vec2{ 0.f, 0.f };
	vertices[2].uv = Vec2{ 1.f, 1.f };
	vertices[3].uv = Vec2{ 1.f, 0.f };

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

void GeometryHelper::CreateQuad(std::shared_ptr<Geometry<VertexTextureNormalData>> geometry)
{
	std::vector<VertexTextureNormalData> vertices;
	vertices.resize(4);

	vertices[0].position = Vec3{ -0.5f, -0.5f, 0.f };
	vertices[1].position = Vec3{ -0.5f, 0.5f, 0.f };
	vertices[2].position = Vec3{ 0.5f, -0.5f, 0.f };
	vertices[3].position = Vec3{ 0.5f, 0.5f, 0.f };

	vertices[0].uv = Vec2{ 0.f, 1.f };
	vertices[1].uv = Vec2{ 0.f, 0.f };
	vertices[2].uv = Vec2{ 1.f, 1.f };
	vertices[3].uv = Vec2{ 1.f, 0.f };

	vertices[0].normal = Vec3{ 0.f, 0.f, -1.f };
	vertices[1].normal = Vec3{ 0.f, 0.f, -1.f };
	vertices[2].normal = Vec3{ 0.f, 0.f, -1.f };
	vertices[3].normal = Vec3{ 0.f, 0.f, -1.f };

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

void GeometryHelper::CreateQuad(std::shared_ptr<Geometry<VertexTextureNormalTangentData>> geometry)
{
	std::vector<VertexTextureNormalTangentData> vertices;
	vertices.resize(4);

	vertices[0].position = Vec3{ -0.5f, -0.5f, 0.f };
	vertices[1].position = Vec3{ -0.5f, 0.5f, 0.f };
	vertices[2].position = Vec3{ 0.5f, -0.5f, 0.f };
	vertices[3].position = Vec3{ 0.5f, 0.5f, 0.f };

	vertices[0].uv = Vec2{ 0.f, 1.f };
	vertices[1].uv = Vec2{ 0.f, 0.f };
	vertices[2].uv = Vec2{ 1.f, 1.f };
	vertices[3].uv = Vec2{ 1.f, 0.f };

	vertices[0].normal = Vec3{ 0.f, 0.f, -1.f };
	vertices[1].normal = Vec3{ 0.f, 0.f, -1.f };
	vertices[2].normal = Vec3{ 0.f, 0.f, -1.f };
	vertices[3].normal = Vec3{ 0.f, 0.f, -1.f };

	vertices[0].tangent = Vec3{ 1.f, 0.f, 0.f };
	vertices[1].tangent = Vec3{ 1.f, 0.f, 0.f };
	vertices[2].tangent = Vec3{ 1.f, 0.f, 0.f };
	vertices[3].tangent = Vec3{ 1.f, 0.f, 0.f };

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

void GeometryHelper::CreateCube(std::shared_ptr<Geometry<VertexTextureData>> geometry)
{
	float w2 = 0.5f;
	float h2 = 0.5f;
	float d2 = 0.5f;

	std::vector<VertexTextureData> vertices(24);

	// Front
	vertices[0] = { Vec3{ -w2, -h2, -d2 }, Vec2{ 0.f, 1.f } };
	vertices[1] = { Vec3{ -w2, +h2, -d2 }, Vec2{ 0.f, 0.f } };
	vertices[2] = { Vec3{ +w2, +h2, -d2 }, Vec2{ 1.f, 0.f } };
	vertices[3] = { Vec3{ +w2, -h2, -d2 }, Vec2{ 1.f, 1.f } };

	// Back
	vertices[4] = { Vec3{ -w2, -h2, +d2 }, Vec2{ 1.f, 1.f } };
	vertices[5] = { Vec3{ +w2, -h2, +d2 }, Vec2{ 0.f, 1.f } };
	vertices[6] = { Vec3{ +w2, +h2, +d2 }, Vec2{ 0.f, 0.f } };
	vertices[7] = { Vec3{ -w2, +h2, +d2 }, Vec2{ 1.f, 0.f } };

	// Up
	vertices[8] = { Vec3{ -w2, +h2, -d2 }, Vec2{ 0.f, 1.f } };
	vertices[9] = { Vec3{ -w2, +h2, +d2 }, Vec2{ 0.f, 0.f } };
	vertices[10] = { Vec3{ +w2, +h2, +d2 }, Vec2{ 1.f, 0.f } };
	vertices[11] = { Vec3{ +w2, +h2, -d2 }, Vec2{ 1.f, 1.f } };

	// Down
	vertices[12] = { Vec3{ -w2, -h2, -d2 }, Vec2{ 1.f, 1.f } };
	vertices[13] = { Vec3{ +w2, -h2, -d2 }, Vec2{ 0.f, 1.f } };
	vertices[14] = { Vec3{ +w2, -h2, +d2 }, Vec2{ 0.f, 0.f } };
	vertices[15] = { Vec3{ -w2, -h2, +d2 }, Vec2{ 1.f, 0.f } };

	// Left
	vertices[16] = { Vec3{ -w2, -h2, +d2 }, Vec2{ 0.f, 1.f } };
	vertices[17] = { Vec3{ -w2, +h2, +d2 }, Vec2{ 0.f, 0.f } };
	vertices[18] = { Vec3{ -w2, +h2, -d2 }, Vec2{ 1.f, 0.f } };
	vertices[19] = { Vec3{ -w2, -h2, -d2 }, Vec2{ 1.f, 1.f } };

	// Right
	vertices[20] = { Vec3{ +w2, -h2, -d2 }, Vec2{ 0.f, 1.f } };
	vertices[21] = { Vec3{ +w2, +h2, -d2 }, Vec2{ 0.f, 0.f } };
	vertices[22] = { Vec3{ +w2, +h2, +d2 }, Vec2{ 1.f, 0.f } };
	vertices[23] = { Vec3{ +w2, -h2, +d2 }, Vec2{ 1.f, 1.f } };

	geometry->SetVertices(vertices);

	std::vector<uint32> indices(36);

	// Front
	indices[0] = 0; indices[1] = 1; indices[2] = 2;
	indices[3] = 2; indices[4] = 3; indices[5] = 0;

	// Back
	indices[6] = 4; indices[7] = 5; indices[8] = 6;
	indices[9] = 6; indices[10] = 7; indices[11] = 4;

	// Up
	indices[12] = 8; indices[13] = 9; indices[14] = 10;
	indices[15] = 10; indices[16] = 11; indices[17] = 8;

	// Down
	indices[18] = 12; indices[19] = 13; indices[20] = 14;
	indices[21] = 14; indices[22] = 15; indices[23] = 12;

	// Left
	indices[24] = 16; indices[25] = 17; indices[26] = 18;
	indices[27] = 18; indices[28] = 19; indices[29] = 16;

	// Right
	indices[30] = 20; indices[31] = 21; indices[32] = 22;
	indices[33] = 22; indices[34] = 23; indices[35] = 20;

	geometry->SetIndices(indices);
}

void GeometryHelper::CreateCube(std::shared_ptr<Geometry<VertexTextureNormalData>> geometry)
{
	float w2 = 0.5f;
	float h2 = 0.5f;
	float d2 = 0.5f;

	std::vector<VertexTextureNormalData> vertices(24);

	// Front
	vertices[0] = { Vec3{ -w2, -h2, -d2 }, Vec2{ 0.f, 1.f }, Vec3(0.0f, 0.0f, -1.0f) };
	vertices[1] = { Vec3{ -w2, +h2, -d2 }, Vec2{ 0.f, 0.f }, Vec3(0.0f, 0.0f, -1.0f) };
	vertices[2] = { Vec3{ +w2, +h2, -d2 }, Vec2{ 1.f, 0.f }, Vec3(0.0f, 0.0f, -1.0f) };
	vertices[3] = { Vec3{ +w2, -h2, -d2 }, Vec2{ 1.f, 1.f }, Vec3(0.0f, 0.0f, -1.0f) };

	// Back
	vertices[4] = { Vec3{ -w2, -h2, +d2 }, Vec2{ 1.f, 1.f }, Vec3(0.0f, 0.0f, 1.0f) };
	vertices[5] = { Vec3{ +w2, -h2, +d2 }, Vec2{ 0.f, 1.f }, Vec3(0.0f, 0.0f, 1.0f) };
	vertices[6] = { Vec3{ +w2, +h2, +d2 }, Vec2{ 0.f, 0.f }, Vec3(0.0f, 0.0f, 1.0f) };
	vertices[7] = { Vec3{ -w2, +h2, +d2 }, Vec2{ 1.f, 0.f }, Vec3(0.0f, 0.0f, 1.0f) };

	// Up
	vertices[8] = { Vec3{ -w2, +h2, -d2 }, Vec2{ 0.f, 1.f }, Vec3(0.0f, 1.0f, 0.0f) };
	vertices[9] = { Vec3{ -w2, +h2, +d2 }, Vec2{ 0.f, 0.f }, Vec3(0.0f, 1.0f, 0.0f) };
	vertices[10] = { Vec3{ +w2, +h2, +d2 }, Vec2{ 1.f, 0.f }, Vec3(0.0f, 1.0f, 0.0f) };
	vertices[11] = { Vec3{ +w2, +h2, -d2 }, Vec2{ 1.f, 1.f }, Vec3(0.0f, 1.0f, 0.0f) };

	// Down
	vertices[12] = { Vec3{ -w2, -h2, -d2 }, Vec2{ 1.f, 1.f }, Vec3(0.0f, -1.0f, 0.0f) };
	vertices[13] = { Vec3{ +w2, -h2, -d2 }, Vec2{ 0.f, 1.f }, Vec3(0.0f, -1.0f, 0.0f) };
	vertices[14] = { Vec3{ +w2, -h2, +d2 }, Vec2{ 0.f, 0.f }, Vec3(0.0f, -1.0f, 0.0f) };
	vertices[15] = { Vec3{ -w2, -h2, +d2 }, Vec2{ 1.f, 0.f }, Vec3(0.0f, -1.0f, 0.0f) };

	// Left
	vertices[16] = { Vec3{ -w2, -h2, +d2 }, Vec2{ 0.f, 1.f }, Vec3(-1.0f, 0.0f, 0.0f) };
	vertices[17] = { Vec3{ -w2, +h2, +d2 }, Vec2{ 0.f, 0.f }, Vec3(-1.0f, 0.0f, 0.0f) };
	vertices[18] = { Vec3{ -w2, +h2, -d2 }, Vec2{ 1.f, 0.f }, Vec3(-1.0f, 0.0f, 0.0f) };
	vertices[19] = { Vec3{ -w2, -h2, -d2 }, Vec2{ 1.f, 1.f }, Vec3(-1.0f, 0.0f, 0.0f) };

	// Right
	vertices[20] = { Vec3{ +w2, -h2, -d2 }, Vec2{ 0.f, 1.f }, Vec3(1.0f, 0.0f, 0.0f) };
	vertices[21] = { Vec3{ +w2, +h2, -d2 }, Vec2{ 0.f, 0.f }, Vec3(1.0f, 0.0f, 0.0f) };
	vertices[22] = { Vec3{ +w2, +h2, +d2 }, Vec2{ 1.f, 0.f }, Vec3(1.0f, 0.0f, 0.0f) };
	vertices[23] = { Vec3{ +w2, -h2, +d2 }, Vec2{ 1.f, 1.f }, Vec3(1.0f, 0.0f, 0.0f) };

	geometry->SetVertices(vertices);

	std::vector<uint32> indices(36);

	// Front
	indices[0] = 0; indices[1] = 1; indices[2] = 2;
	indices[3] = 2; indices[4] = 3; indices[5] = 0;

	// Back
	indices[6] = 4; indices[7] = 5; indices[8] = 6;
	indices[9] = 6; indices[10] = 7; indices[11] = 4;

	// Up
	indices[12] = 8; indices[13] = 9; indices[14] = 10;
	indices[15] = 10; indices[16] = 11; indices[17] = 8;

	// Down
	indices[18] = 12; indices[19] = 13; indices[20] = 14;
	indices[21] = 14; indices[22] = 15; indices[23] = 12;

	// Left
	indices[24] = 16; indices[25] = 17; indices[26] = 18;
	indices[27] = 18; indices[28] = 19; indices[29] = 16;

	// Right
	indices[30] = 20; indices[31] = 21; indices[32] = 22;
	indices[33] = 22; indices[34] = 23; indices[35] = 20;

	geometry->SetIndices(indices);
}

void GeometryHelper::CreateCube(std::shared_ptr<Geometry<VertexTextureNormalTangentData>> geometry)
{
	float w2 = 0.5f;
	float h2 = 0.5f;
	float d2 = 0.5f;

	std::vector<VertexTextureNormalTangentData> vertices(24);

	// æ’∏È
	vertices[0] = VertexTextureNormalTangentData(Vec3(-w2, -h2, -d2), Vec2(0.0f, 1.0f), Vec3(0.0f, 0.0f, -1.0f), Vec3(1.0f, 0.0f, 0.0f));
	vertices[1] = VertexTextureNormalTangentData(Vec3(-w2, +h2, -d2), Vec2(0.0f, 0.0f), Vec3(0.0f, 0.0f, -1.0f), Vec3(1.0f, 0.0f, 0.0f));
	vertices[2] = VertexTextureNormalTangentData(Vec3(+w2, +h2, -d2), Vec2(1.0f, 0.0f), Vec3(0.0f, 0.0f, -1.0f), Vec3(1.0f, 0.0f, 0.0f));
	vertices[3] = VertexTextureNormalTangentData(Vec3(+w2, -h2, -d2), Vec2(1.0f, 1.0f), Vec3(0.0f, 0.0f, -1.0f), Vec3(1.0f, 0.0f, 0.0f));
	// µﬁ∏È
	vertices[4] = VertexTextureNormalTangentData(Vec3(-w2, -h2, +d2), Vec2(1.0f, 1.0f), Vec3(0.0f, 0.0f, 1.0f), Vec3(-1.0f, 0.0f, 0.0f));
	vertices[5] = VertexTextureNormalTangentData(Vec3(+w2, -h2, +d2), Vec2(0.0f, 1.0f), Vec3(0.0f, 0.0f, 1.0f), Vec3(-1.0f, 0.0f, 0.0f));
	vertices[6] = VertexTextureNormalTangentData(Vec3(+w2, +h2, +d2), Vec2(0.0f, 0.0f), Vec3(0.0f, 0.0f, 1.0f), Vec3(-1.0f, 0.0f, 0.0f));
	vertices[7] = VertexTextureNormalTangentData(Vec3(-w2, +h2, +d2), Vec2(1.0f, 0.0f), Vec3(0.0f, 0.0f, 1.0f), Vec3(-1.0f, 0.0f, 0.0f));
	// ¿≠∏È
	vertices[8] = VertexTextureNormalTangentData(Vec3(-w2, +h2, -d2), Vec2(0.0f, 1.0f), Vec3(0.0f, 1.0f, 0.0f), Vec3(1.0f, 0.0f, 0.0f));
	vertices[9] = VertexTextureNormalTangentData(Vec3(-w2, +h2, +d2), Vec2(0.0f, 0.0f), Vec3(0.0f, 1.0f, 0.0f), Vec3(1.0f, 0.0f, 0.0f));
	vertices[10] = VertexTextureNormalTangentData(Vec3(+w2, +h2, +d2), Vec2(1.0f, 0.0f), Vec3(0.0f, 1.0f, 0.0f), Vec3(1.0f, 0.0f, 0.0f));
	vertices[11] = VertexTextureNormalTangentData(Vec3(+w2, +h2, -d2), Vec2(1.0f, 1.0f), Vec3(0.0f, 1.0f, 0.0f), Vec3(1.0f, 0.0f, 0.0f));
	// æ∆∑ß∏È
	vertices[12] = VertexTextureNormalTangentData(Vec3(-w2, -h2, -d2), Vec2(1.0f, 1.0f), Vec3(0.0f, -1.0f, 0.0f), Vec3(-1.0f, 0.0f, 0.0f));
	vertices[13] = VertexTextureNormalTangentData(Vec3(+w2, -h2, -d2), Vec2(0.0f, 1.0f), Vec3(0.0f, -1.0f, 0.0f), Vec3(-1.0f, 0.0f, 0.0f));
	vertices[14] = VertexTextureNormalTangentData(Vec3(+w2, -h2, +d2), Vec2(0.0f, 0.0f), Vec3(0.0f, -1.0f, 0.0f), Vec3(-1.0f, 0.0f, 0.0f));
	vertices[15] = VertexTextureNormalTangentData(Vec3(-w2, -h2, +d2), Vec2(1.0f, 0.0f), Vec3(0.0f, -1.0f, 0.0f), Vec3(-1.0f, 0.0f, 0.0f));
	// øﬁ¬ ∏È
	vertices[16] = VertexTextureNormalTangentData(Vec3(-w2, -h2, +d2), Vec2(0.0f, 1.0f), Vec3(-1.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, -1.0f));
	vertices[17] = VertexTextureNormalTangentData(Vec3(-w2, +h2, +d2), Vec2(0.0f, 0.0f), Vec3(-1.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, -1.0f));
	vertices[18] = VertexTextureNormalTangentData(Vec3(-w2, +h2, -d2), Vec2(1.0f, 0.0f), Vec3(-1.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, -1.0f));
	vertices[19] = VertexTextureNormalTangentData(Vec3(-w2, -h2, -d2), Vec2(1.0f, 1.0f), Vec3(-1.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, -1.0f));
	// ø¿∏•¬ ∏È
	vertices[20] = VertexTextureNormalTangentData(Vec3(+w2, -h2, -d2), Vec2(0.0f, 1.0f), Vec3(1.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 1.0f));
	vertices[21] = VertexTextureNormalTangentData(Vec3(+w2, +h2, -d2), Vec2(0.0f, 0.0f), Vec3(1.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 1.0f));
	vertices[22] = VertexTextureNormalTangentData(Vec3(+w2, +h2, +d2), Vec2(1.0f, 0.0f), Vec3(1.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 1.0f));
	vertices[23] = VertexTextureNormalTangentData(Vec3(+w2, -h2, +d2), Vec2(1.0f, 1.0f), Vec3(1.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 1.0f));

	geometry->SetVertices(vertices);

	std::vector<uint32> idx(36);

	// æ’∏È
	idx[0] = 0; idx[1] = 1; idx[2] = 2;
	idx[3] = 0; idx[4] = 2; idx[5] = 3;
	// µﬁ∏È
	idx[6] = 4; idx[7] = 5; idx[8] = 6;
	idx[9] = 4; idx[10] = 6; idx[11] = 7;
	// ¿≠∏È
	idx[12] = 8; idx[13] = 9; idx[14] = 10;
	idx[15] = 8; idx[16] = 10; idx[17] = 11;
	// æ∆∑ß∏È
	idx[18] = 12; idx[19] = 13; idx[20] = 14;
	idx[21] = 12; idx[22] = 14; idx[23] = 15;
	// øﬁ¬ ∏È
	idx[24] = 16; idx[25] = 17; idx[26] = 18;
	idx[27] = 16; idx[28] = 18; idx[29] = 19;
	// ø¿∏•¬ ∏È
	idx[30] = 20; idx[31] = 21; idx[32] = 22;
	idx[33] = 20; idx[34] = 22; idx[35] = 23;

	geometry->SetIndices(idx);
}

void GeometryHelper::CreateSphere(std::shared_ptr<Geometry<VertexTextureData>> geometry)
{
	float radius = 0.5f;
	uint32 stackCount = 20; // ∞°∑Œ 
	uint32 sliceCount = 20; // ºº∑Œ

	std::vector<VertexTextureData> vertices;

	VertexTextureData vertex;

	// Top vertex
	vertex.position = Vec3{ 0.f, radius, 0.f };
	vertex.uv = Vec2{ 0.5f, 0.f };
	vertices.push_back(vertex);

	float stackAngle = XM_PI / stackCount;
	float sliceAngle = XM_2PI / sliceCount;

	float deltaU = 1.f / static_cast<float>(sliceCount);
	float deltaV = 1.f / static_cast<float>(stackCount);

	for (uint32 y = 1; y < stackCount; ++y)
	{
		float phi = stackAngle * y;
		float posY = radius * cosf(phi);
		float r = radius * sinf(phi);

		for (uint32 x = 0; x <= sliceCount; ++x)
		{
			float theta = sliceAngle * x;
			float posX = r * cosf(theta);
			float z = r * sinf(theta);

			vertex.position = Vec3{ posX, posY, z };
			vertex.uv = Vec2{ x * deltaU, y * deltaV };
			vertices.push_back(vertex);
		}
	}

	// Bottom vertex
	vertex.position = Vec3{ 0.f, -radius, 0.f };
	vertex.uv = Vec2{ 0.5f, 1.f };
	vertices.push_back(vertex);

	geometry->SetVertices(vertices);

	std::vector<uint32> indices;
	
	// Top cap
	for (uint32 i = 0; i <= sliceCount; ++i)
	{
		indices.push_back(0);
		indices.push_back(i + 2);
		indices.push_back(i + 1);
	}

	// Middle stacks
	uint32 ringVertexCount = sliceCount + 1;
	for (uint32 y = 0; y < stackCount - 2; ++y)
	{
		for (uint32 x = 0; x < sliceCount; ++x)
		{
			indices.push_back(1 + y * ringVertexCount + x);
			indices.push_back(1 + y * ringVertexCount + (x + 1));
			indices.push_back(1 + (y + 1) * ringVertexCount + x);

			indices.push_back(1 + (y + 1) * ringVertexCount + x);
			indices.push_back(1 + y * ringVertexCount + (x + 1));
			indices.push_back(1 + (y + 1) * ringVertexCount + (x + 1));
		}
	}

	// Bottom cap
	uint32 bottomIndex = static_cast<uint32>(vertices.size()) - 1;
	uint32 lastRingStartIndex = bottomIndex - ringVertexCount;
	for (uint32 i = 1; i < sliceCount; ++i)
	{
		indices.push_back(bottomIndex);
		indices.push_back(lastRingStartIndex + i);
		indices.push_back(lastRingStartIndex + i + 1);
	}

	geometry->SetIndices(indices);
}

void GeometryHelper::CreateSphere(std::shared_ptr<Geometry<VertexTextureNormalData>> geometry)
{
	float radius = 0.5f;
	uint32 stackCount = 20; // ∞°∑Œ 
	uint32 sliceCount = 20; // ºº∑Œ

	std::vector<VertexTextureNormalData> vertices;

	VertexTextureNormalData vertex;

	// Top vertex
	vertex.position = Vec3{ 0.f, radius, 0.f };
	vertex.uv = Vec2{ 0.5f, 0.f };

	vertex.normal = vertex.position;
	vertex.normal.Normalize();

	vertices.push_back(vertex);

	float stackAngle = XM_PI / stackCount;
	float sliceAngle = XM_2PI / sliceCount;

	float deltaU = 1.f / static_cast<float>(sliceCount);
	float deltaV = 1.f / static_cast<float>(stackCount);

	for (uint32 y = 1; y < stackCount; ++y)
	{
		float phi = stackAngle * y;
		float posY = radius * cosf(phi);
		float r = radius * sinf(phi);

		for (uint32 x = 0; x <= sliceCount; ++x)
		{
			float theta = sliceAngle * x;
			float posX = r * cosf(theta);
			float z = r * sinf(theta);

			vertex.position = Vec3{ posX, posY, z };
			vertex.uv = Vec2{ x * deltaU, y * deltaV };

			// Normal
			vertex.normal = vertex.position;
			vertex.normal.Normalize();

			vertices.push_back(vertex);
		}
	}

	// Bottom vertex
	vertex.position = Vec3{ 0.f, -radius, 0.f };
	vertex.uv = Vec2{ 0.5f, 1.f };

	vertex.normal = vertex.position;
	vertex.normal.Normalize();

	vertices.push_back(vertex);

	geometry->SetVertices(vertices);

	std::vector<uint32> indices;

	// Top cap
	for (uint32 i = 0; i <= sliceCount; ++i)
	{
		indices.push_back(0);
		indices.push_back(i + 2);
		indices.push_back(i + 1);
	}

	// Middle stacks
	uint32 ringVertexCount = sliceCount + 1;
	for (uint32 y = 0; y < stackCount - 2; ++y)
	{
		for (uint32 x = 0; x < sliceCount; ++x)
		{
			indices.push_back(1 + y * ringVertexCount + x);
			indices.push_back(1 + y * ringVertexCount + (x + 1));
			indices.push_back(1 + (y + 1) * ringVertexCount + x);

			indices.push_back(1 + (y + 1) * ringVertexCount + x);
			indices.push_back(1 + y * ringVertexCount + (x + 1));
			indices.push_back(1 + (y + 1) * ringVertexCount + (x + 1));
		}
	}

	// Bottom cap
	uint32 bottomIndex = static_cast<uint32>(vertices.size()) - 1;
	uint32 lastRingStartIndex = bottomIndex - ringVertexCount;
	for (uint32 i = 1; i < sliceCount; ++i)
	{
		indices.push_back(bottomIndex);
		indices.push_back(lastRingStartIndex + i);
		indices.push_back(lastRingStartIndex + i + 1);
	}

	geometry->SetIndices(indices);
}

void GeometryHelper::CreateSphere(std::shared_ptr<Geometry<VertexTextureNormalTangentData>> geometry)
{
	float radius = 0.5f; // ±∏¿« π›¡ˆ∏ß
	uint32 stackCount = 20; // ∞°∑Œ ∫–«“
	uint32 sliceCount = 20; // ºº∑Œ ∫–«“

	std::vector<VertexTextureNormalTangentData> vertices;

	VertexTextureNormalTangentData vertex;

	// ∫œ±ÿ
	vertex.position = Vec3(0.0f, radius, 0.0f);
	vertex.uv = Vec2(0.5f, 0.0f);
	vertex.normal = vertex.position;
	vertex.normal.Normalize();
	vertex.tangent = Vec3(1.0f, 0.0f, 0.0f);
	vertex.tangent.Normalize();
	vertices.push_back(vertex);

	float stackAngle = XM_PI / stackCount;
	float sliceAngle = XM_2PI / sliceCount;

	float deltaU = 1.f / static_cast<float>(sliceCount);
	float deltaV = 1.f / static_cast<float>(stackCount);

	// ∞Ì∏Æ∏∂¥Ÿ µπ∏Èº≠ ¡§¡°¿ª ∞ËªÍ«—¥Ÿ (∫œ±ÿ/≥≤±ÿ ¥‹¿œ¡°¿∫ ∞Ì∏Æ∞° X)
	for (uint32 y = 1; y <= stackCount - 1; ++y)
	{
		float phi = y * stackAngle;

		// ∞Ì∏Æø° ¿ßƒ°«— ¡§¡°
		for (uint32 x = 0; x <= sliceCount; ++x)
		{
			float theta = x * sliceAngle;

			vertex.position.x = radius * sinf(phi) * cosf(theta);
			vertex.position.y = radius * cosf(phi);
			vertex.position.z = radius * sinf(phi) * sinf(theta);

			vertex.uv = Vec2(deltaU * x, deltaV * y);

			vertex.normal = vertex.position;
			vertex.normal.Normalize();

			vertex.tangent.x = -radius * sinf(phi) * sinf(theta);
			vertex.tangent.y = 0.0f;
			vertex.tangent.z = radius * sinf(phi) * cosf(theta);
			vertex.tangent.Normalize();

			vertices.push_back(vertex);
		}
	}

	// ≥≤±ÿ
	vertex.position = Vec3(0.0f, -radius, 0.0f);
	vertex.uv = Vec2(0.5f, 1.0f);
	vertex.normal = vertex.position;
	vertex.normal.Normalize();
	vertex.tangent = Vec3(1.0f, 0.0f, 0.0f);
	vertex.tangent.Normalize();
	vertices.push_back(vertex);

	geometry->SetVertices(vertices);

	std::vector<uint32> indices(36);

	// ∫œ±ÿ ¿Œµ¶Ω∫
	for (uint32 i = 0; i <= sliceCount; ++i)
	{
		//  [0]
		//   |  \
		//  [i+1]-[i+2]
		indices.push_back(0);
		indices.push_back(i + 2);
		indices.push_back(i + 1);
	}

	// ∏ˆ≈Î ¿Œµ¶Ω∫
	uint32 ringVertexCount = sliceCount + 1;
	for (uint32 y = 0; y < stackCount - 2; ++y)
	{
		for (uint32 x = 0; x < sliceCount; ++x)
		{
			//  [y, x]-[y, x+1]
			//  |		/
			//  [y+1, x]
			indices.push_back(1 + (y)*ringVertexCount + (x));
			indices.push_back(1 + (y)*ringVertexCount + (x + 1));
			indices.push_back(1 + (y + 1) * ringVertexCount + (x));
			//		 [y, x+1]
			//		 /	  |
			//  [y+1, x]-[y+1, x+1]
			indices.push_back(1 + (y + 1) * ringVertexCount + (x));
			indices.push_back(1 + (y)*ringVertexCount + (x + 1));
			indices.push_back(1 + (y + 1) * ringVertexCount + (x + 1));
		}
	}

	// ≥≤±ÿ ¿Œµ¶Ω∫
	uint32 bottomIndex = static_cast<uint32>(vertices.size()) - 1;
	uint32 lastRingStartIndex = bottomIndex - ringVertexCount;
	for (uint32 i = 0; i < sliceCount; ++i)
	{
		//  [last+i]-[last+i+1]
		//  |      /
		//  [bottom]
		indices.push_back(bottomIndex);
		indices.push_back(lastRingStartIndex + i);
		indices.push_back(lastRingStartIndex + i + 1);
	}

	geometry->SetIndices(indices);
}

void GeometryHelper::CreateGrid(std::shared_ptr<Geometry<VertexTextureData>> geometry, int32 sizeX, int32 sizeZ)
{
	std::vector<VertexTextureData> vertices;

	for (int32 z = 0; z < sizeZ + 1; z++)
	{
		for (int32 x = 0; x < sizeX + 1; x++)
		{
			VertexTextureData vertex;
			vertex.position = Vec3{ static_cast<float>(x), 0.f, static_cast<float>(z) };
			vertex.uv = Vec2{ static_cast<float>(x), static_cast<float>(sizeZ - z) };
			vertices.push_back(vertex);
		}
	}

	geometry->SetVertices(vertices);

	std::vector<uint32> indices;

	for (int32 z = 0; z < sizeZ; z++)
	{
		for (int32 x = 0; x < sizeX; x++)
		{
			indices.push_back((sizeX + 1) * (z + 1) + x);
			indices.push_back((sizeX + 1) * z + x + 1);
			indices.push_back((sizeX + 1) * z + x);
			
			indices.push_back((sizeX + 1) * (z) + (x + 1));
			indices.push_back((sizeX + 1) * (z + 1) + x);
			indices.push_back((sizeX + 1) * (z + 1) + (x + 1));
		}
	}

	geometry->SetIndices(indices);
}

void GeometryHelper::CreateGrid(std::shared_ptr<Geometry<VertexTextureNormalData>> geometry, int32 sizeX, int32 sizeZ)
{
	std::vector<VertexTextureNormalData> vertices;

	for (int32 z = 0; z < sizeZ + 1; z++)
	{
		for (int32 x = 0; x < sizeX + 1; x++)
		{
			VertexTextureNormalData vertex;
			vertex.position = Vec3{ static_cast<float>(x), 0.f, static_cast<float>(z) };
			vertex.uv = Vec2{ static_cast<float>(x), static_cast<float>(sizeZ - z) };
			vertex.normal = Vec3{ 0.f, 1.f, 0.f };
			vertices.push_back(vertex);
		}
	}

	geometry->SetVertices(vertices);

	std::vector<uint32> indices;

	for (int32 z = 0; z < sizeZ; z++)
	{
		for (int32 x = 0; x < sizeX; x++)
		{
			indices.push_back((sizeX + 1) * (z + 1) + x);
			indices.push_back((sizeX + 1) * z + x + 1);
			indices.push_back((sizeX + 1) * z + x);

			indices.push_back((sizeX + 1) * (z)+(x + 1));
			indices.push_back((sizeX + 1) * (z + 1) + x);
			indices.push_back((sizeX + 1) * (z + 1) + (x + 1));
		}
	}

	geometry->SetIndices(indices);
}

void GeometryHelper::CreateGrid(std::shared_ptr<Geometry<VertexTextureNormalTangentData>> geometry, int32 sizeX, int32 sizeZ)
{
	std::vector<VertexTextureNormalTangentData> vertices;

	for (int32 z = 0; z < sizeZ + 1; z++)
	{
		for (int32 x = 0; x < sizeX + 1; x++)
		{
			VertexTextureNormalTangentData v;
			v.position = Vec3(static_cast<float>(x), 0, static_cast<float>(z));
			v.uv = Vec2(static_cast<float>(x), static_cast<float>(sizeZ - z));
			v.normal = Vec3(0.f, 1.f, 0.f);
			v.tangent = Vec3(1.f, 0.f, 0.f);

			vertices.push_back(v);
		}
	}

	geometry->SetVertices(vertices);

	std::vector<uint32> indices;

	for (int32 z = 0; z < sizeZ; z++)
	{
		for (int32 x = 0; x < sizeX; x++)
		{
			//  [0]
			//   |	\
			//  [2] - [1]
			indices.push_back((sizeX + 1) * (z + 1) + (x));
			indices.push_back((sizeX + 1) * (z)+(x + 1));
			indices.push_back((sizeX + 1) * (z)+(x));
			//  [1] - [2]
			//   	\  |
			//		  [0]
			indices.push_back((sizeX + 1) * (z)+(x + 1));
			indices.push_back((sizeX + 1) * (z + 1) + (x));
			indices.push_back((sizeX + 1) * (z + 1) + (x + 1));
		}
	}

	geometry->SetIndices(indices);
}