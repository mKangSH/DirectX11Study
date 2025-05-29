#pragma once

class asAnimation;
class asAnimationNode;

class Converter
{
public:
	Converter();
	~Converter();

public:
	void ReadAssetFile(const std::wstring& path);
	void ExportModelData(const std::wstring& savePath);
	void ExportMaterialData(const std::wstring& savePath);
	void ExportAnimationData(const std::wstring& savePath, uint32 index = 0);

private:
	void ReadModelData(aiNode* node, int32 index, int32 parentIndex );
	void ReadMeshData(aiNode* node, int32 bone);
	void ReadSkinData();
	void WriteModelFile(std::wstring finalPath);

private:
	std::shared_ptr<asAnimation> ReadAnimationData(const aiAnimation* srcAnimation);
	std::shared_ptr<asAnimationNode> ParseAnimationNode(std::shared_ptr<asAnimation> animation, aiNodeAnim* srcNode);
	void ReadKeyframeData(std::shared_ptr<asAnimation> animation, aiNode* srcNode, std::map<std::string, std::shared_ptr<asAnimationNode>>& cache);
	void WriteAnimationFile(std::shared_ptr<asAnimation> animation, std::wstring finalPath);

private:
	void ReadMaterialData();
	void WriteMaterialData(std::wstring finalPath);
	std::string WriteTexture(std::string saveFolder, std::string file);

	uint32 GetBoneIndex(const std::string& name) const;

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

