#include "pch.h"
#include "ModelMesh.h"

void ModelMesh::CreateBuffers()
{
	vertexBuffer = std::make_shared<VertexBuffer>();
	vertexBuffer->CreateBuffer(geometry->GetVertices());

	indexBuffer = std::make_shared<IndexBuffer>();
	indexBuffer->CreateBuffer(geometry->GetIndices());
}