#pragma once

#include "../00.Engine/Resource/ResourceBase.h"

class Shader;
class Texture;
class Mesh;
class Material;

class ResourceManager
{
	DECLARE_SINGLETON(ResourceManager)

public:
	void Init(const std::wstring& resourcePath);

	template <typename T>
	std::shared_ptr<T> Load(const std::wstring& key, const std::wstring& path);

	template <typename T>
	bool Add(const std::wstring& key, const std::shared_ptr<T>& object);

	template <typename T>
	std::shared_ptr<T> Get(const std::wstring& key);

	// Get<Texture>() 
	template <typename T>
	ResourceType GetResourceType();

private:
	void CreateDefaultMesh();

private:
	std::wstring _resourcePath;

private:
	using KeyObjMap = std::map<std::wstring, std::shared_ptr<ResourceBase>>;
	std::array<KeyObjMap, RESOURCE_TYPE_COUNT> _resourceMapArray;
};

template<typename T>
inline std::shared_ptr<T> ResourceManager::Load(const std::wstring& key, const std::wstring& path)
{
	ResourceType resourceType = GetResourceType<T>();
	if (resourceType == ResourceType::None)
	{
		assert(false);
		return nullptr;
	}

	KeyObjMap& keyObjMap = _resourceMapArray[static_cast<int8>(resourceType)];
	auto iter = keyObjMap.find(key);
	if (iter != keyObjMap.end())
	{
		return std::static_pointer_cast<T>(iter->second);
	}

	std::shared_ptr<T> object = std::make_shared<T>(resourceType);

	std::wstring filePath = _resourcePath + path;
	object->Load(filePath);
	keyObjMap[key] = object;

	return object;
}

template<typename T>
inline bool ResourceManager::Add(const std::wstring& key, const std::shared_ptr<T>& object)
{
	ResourceType resourceType = GetResourceType<T>();
	if (resourceType == ResourceType::None)
	{
		assert(false);
		return false;
	}

	KeyObjMap& keyObjMap = _resourceMapArray[static_cast<int8>(resourceType)];
	auto iter = keyObjMap.find(key);
	if (iter != keyObjMap.end())
	{
		return false;
	}

	keyObjMap[key] = object;
	return true;
}

template<typename T>
inline std::shared_ptr<T> ResourceManager::Get(const std::wstring& key)
{
	ResourceType resourceType = GetResourceType<T>();
	if (resourceType == ResourceType::None)
	{
		assert(false);
		return nullptr;
	}

	KeyObjMap& keyObjMap = _resourceMapArray[static_cast<int8>(resourceType)];
	auto iter = keyObjMap.find(key);
	if (iter != keyObjMap.end())
	{
		return std::static_pointer_cast<T>(iter->second);
	}

	return nullptr;
}

template<typename T>
inline ResourceType ResourceManager::GetResourceType()
{
	if (std::is_same_v<T, Texture>)	
	{
		return ResourceType::Texture;
	}
	else if (std::is_same_v<T, Mesh>)
	{
		return ResourceType::Mesh;
	}
	else if (std::is_same_v<T, Material>)
	{
		return ResourceType::Material;
	}
	else
	{
		assert(false);
		return ResourceType::None;
	}
}
