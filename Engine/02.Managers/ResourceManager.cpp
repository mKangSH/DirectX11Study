#include "pch.h"
#include "ResourceManager.h"
#include "../00.Engine/Resource/Mesh.h"
#include "../01.Graphics/Buffer/GeometryHelper.h"

void ResourceManager::Init(const std::wstring& resourcePath)
{
	_resourcePath = resourcePath;

	CreateDefaultMesh();
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