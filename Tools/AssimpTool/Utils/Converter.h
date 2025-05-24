#pragma once

class Converter
{
public:
	Converter();
	~Converter();

public:
	void ReadAssetFile(const std::wstring& path);
	void ExportModelData(const std::wstring& savePath);
	void ExportMaterialData(const std::wstring& savePath);

private:
	void ReadModelData(aiNode* node, int32 index, int32 parentIndex );
	void ReadMeshData(aiNode* node, int32 bone);
	void WriteModelFile(std::wstring finalPath);

private:
	void ReadMaterialData();
	void WriteMaterialData(std::wstring finalPath);
	std::string WriteTexture(std::string saveFolder, std::string file);

private:
	std::wstring _assetPath = L"../../Resources/Assets/";
	std::wstring _modelPath = L"../../Resources/Models/";
	std::wstring _texturePath = L"../../Resources/Textures/";

private:
	std::shared_ptr<Assimp::Importer> _importer;
	const aiScene* _scene = nullptr;

private:
	std::vector<std::shared_ptr<class asBone>> _bones;
	std::vector<std::shared_ptr<class asMesh>> _meshes;
	std::vector<std::shared_ptr<class asMaterial>> _materials;
};

