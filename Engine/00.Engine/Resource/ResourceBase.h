#pragma once

enum class ResourceType : int8
{
	None = -1,
	Mesh,
	Shader,
	Texture,
	Material,
	Animation,

	End
};

enum
{
	RESOURCE_TYPE_COUNT = static_cast<int8>(ResourceType::End)
};

class ResourceBase : public std::enable_shared_from_this<ResourceBase>
{
public:
	ResourceBase(ResourceType type);
	virtual ~ResourceBase();

public:
	ResourceType GetType() const { return _type; }
	const std::wstring& GetName() const { return _name; }
	uint32 GetID() const { return _id; }

	void SetName(const std::wstring& name) { _name = name; }

protected:
	virtual void Load(const std::wstring& path) {}
	virtual void Save(const std::wstring& path) {}

protected:
	ResourceType _type = ResourceType::None;
	std::wstring _name;
	std::wstring _path;
	uint32 _id = 0;
};

