#pragma once

using VertexType = VertexTextureNormalTangentBlendData;

struct asBone
{
	std::string name;
	int32 index = -1;
	int32 parentIndex = -1;
	Matrix transform;
};

struct asMesh
{
	std::string name;
	aiMesh* mesh;
	std::vector<VertexType> vertices;
	std::vector<uint32> indices;

	// material 및 bone mapping용 추가정보
	int32 boneIndex;
	std::string materialName;
};

struct asMaterial
{
	std::string name;
	Vec4 ambient;
	Vec4 diffuse;
	Vec4 specular;
	Vec4 emissive;
	std::string diffuseFile;
	std::string specularFile;
	std::string normalFile;
};