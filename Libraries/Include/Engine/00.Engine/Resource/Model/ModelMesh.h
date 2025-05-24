#pragma once

struct ModelBone
{
	std::wstring name;
	int32 index;
	int32 parentIndex;
	std::shared_ptr<ModelBone> parent; // Cache

	Matrix transform;
	std::vector<std::shared_ptr<ModelBone>> children; // Cache
};

struct ModelMesh
{
	void CreateBuffers();

	std::wstring name;

	// Mesh
	std::shared_ptr<Geometry<ModelVertexType>> geometry = std::make_shared<Geometry<ModelVertexType>>();
	std::shared_ptr<VertexBuffer> vertexBuffer = nullptr;
	std::shared_ptr<IndexBuffer> indexBuffer = nullptr;

	// Material
	std::wstring materialName = L"";
	std::shared_ptr<Material> material = nullptr; // Cache

	// Bones
	int32 boneIndex;
	std::shared_ptr<ModelBone> bone = nullptr; // Cache
};

