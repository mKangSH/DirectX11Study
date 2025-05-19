#pragma once
#include "Engine/01.Graphics/Buffer/Geometry.h"
#include "ResourceBase.h"

class Mesh : public ResourceBase
{
	using Super = ResourceBase;

public:
	Mesh();
	virtual ~Mesh();

public:
	void CreateQuad();
	void CreateCube();
	void CreateSphere();
	void CreateGrid(int32 sizeX, int32 sizeZ);

	std::shared_ptr<VertexBuffer> GetVertexBuffer() const { return _vertexBuffer; }
	std::shared_ptr<IndexBuffer> GetIndexBuffer() const { return _indexBuffer; }

private:
	void CreateBuffers();

private:
	std::shared_ptr<Geometry<VertexTextureNormalTangentData>> _geometry = nullptr;
	std::shared_ptr<VertexBuffer> _vertexBuffer = nullptr;
	std::shared_ptr<IndexBuffer> _indexBuffer = nullptr;
};

