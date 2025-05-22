#include "pch.h"
#include "ResourceManager.h"
#include "../00.Engine/Resource/Mesh.h"
#include "../00.Engine/Resource/Texture.h"
#include "../01.Graphics/Shader/Shader.h"
#include <filesystem>

void ResourceManager::Init(const std::wstring& resourcePath)
{
	_resourcePath = resourcePath;

	CreateDefaultMesh();
}

std::shared_ptr<Texture> ResourceManager::GetOrAddTexture(const std::wstring& key, const std::wstring& path)
{
	std::shared_ptr<Texture> texture = Get<Texture>(key);

	if (std::filesystem::exists(std::filesystem::path(path)) == false)
	{
		return nullptr;
	}

	texture = Load<Texture>(key, path);

	if (texture == nullptr)
	{
		texture = std::make_shared<Texture>();
		texture->Load(path);
		Add(key, texture);
	}

	return texture;
}

void ResourceManager::CreateDefaultMesh()
{
	{
		std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();
		mesh->CreateQuad();
		Add(L"Quad", mesh);
	}

	{
		std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();
		mesh->CreateCube();
		Add(L"Cube", mesh);
	}

	{
		std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();
		mesh->CreateSphere();
		Add(L"Sphere", mesh);
	}
}