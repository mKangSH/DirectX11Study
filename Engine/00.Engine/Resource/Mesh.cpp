#include "pch.h"
#include "Mesh.h"
#include "../01.Graphics/Buffer/GeometryHelper.h"

Mesh::Mesh() : Super(ResourceType::Mesh)
{
}

Mesh::~Mesh()
{

}

void Mesh::CreateQuad()
{
	_geometry = std::make_shared<Geometry<VertexTextureNormalTangentData>>();
	GeometryHelper::CreateQuad(_geometry);
	CreateBuffers();
}

void Mesh::CreateCube()
{
	_geometry = std::make_shared<Geometry<VertexTextureNormalTangentData>>();
	GeometryHelper::CreateCube(_geometry);
	CreateBuffers();
}

void Mesh::CreateSphere()
{
	_geometry = std::make_shared<Geometry<VertexTextureNormalTangentData>>();
	GeometryHelper::CreateSphere(_geometry);
	CreateBuffers();
}

void Mesh::CreateGrid(int32 sizeX, int32 sizeZ)
{
	_geometry = std::make_shared<Geometry<VertexTextureNormalTangentData>>();
	GeometryHelper::CreateGrid(_geometry, sizeX, sizeZ);
	CreateBuffers();
}

void Mesh::CreateBuffers()
{
	_vertexBuffer = std::make_shared<VertexBuffer>();
	_vertexBuffer->CreateBuffer(_geometry->GetVertices());

	_indexBuffer = std::make_shared<IndexBuffer>();
	_indexBuffer->CreateBuffer(_geometry->GetIndices());
}