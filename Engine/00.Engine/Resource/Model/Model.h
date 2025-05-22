#pragma once

class Model : public std::enable_shared_from_this<Model>
{
public:
	Model();
	~Model();

public:
	void ReadMaterial(const std::wstring& fileName);
	void ReadModel(const std::wstring& fileName);

	uint32 GetMaterialCount() { return static_cast<uint32>(_materials.size()); }
	std::vector<std::shared_ptr<Material>>& GetMaterials() { return _materials; }
	std::shared_ptr<Material> GetMaterialByIndex(uint32 index) { return _materials[index]; }
	std::shared_ptr<Material> GetMaterialByName(const std::wstring& name);

	uint32 GetMeshCount() { return static_cast<uint32>(_meshes.size()); }
	std::vector<std::shared_ptr<struct ModelMesh>>& GetMeshes() { return _meshes; }
	std::shared_ptr<struct ModelMesh> GetMeshByIndex(uint32 index) { return _meshes[index]; }
	std::shared_ptr<struct ModelMesh> GetMeshByName(const std::wstring& name);

	uint32 GetBoneCount() { return static_cast<uint32>(_bones.size()); }
	std::vector<std::shared_ptr<struct ModelBone>>& GetBones() { return _bones; }
	std::shared_ptr<struct ModelBone> GetBoneByIndex(uint32 index) { return (index < 0 || index >= _bones.size() ? nullptr : _bones[index]); }
	std::shared_ptr<struct ModelBone> GetBoneByName(const std::wstring& name);

private:
	void BindCacheInfo();

private:
	std::wstring _modelPath = L"../../Resources/Models/";
	std::wstring _texturePath = L"../../Resources/Textures/";

private:
	std::shared_ptr<struct ModelBone> _root = nullptr;
	std::vector<std::shared_ptr<Material>> _materials;
	std::vector<std::shared_ptr<struct ModelBone>> _bones;
	std::vector<std::shared_ptr<struct ModelMesh>> _meshes;
};

