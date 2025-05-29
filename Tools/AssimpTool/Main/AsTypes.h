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

// Animation

struct asBlendWeight
{
	Vec4 indices = Vec4::Zero;
	Vec4 weights = Vec4::Zero;

	void Set(uint32 index, uint32 boneIndex, float weight)
	{
		float i = static_cast<float>(boneIndex);
		float w = weight;

		switch (index)
		{
			case 0: indices.x = i; weights.x = w; break;
			case 1: indices.y = i; weights.y = w; break;
			case 2: indices.z = i; weights.z = w; break;
			case 3: indices.w = i; weights.w = w; break;
		}
	}
};

struct asBoneWeights
{
	using Pair = std::pair<int32, float>;
	std::vector<Pair> boneWeights;

	void AddWeights(int32 boneIndex, float weight)
	{
		if (weight <= 0.0f)
		{
			return;
		}

		auto findIt = std::find_if(boneWeights.begin(), boneWeights.end(),
			[weight](const Pair& p) { return weight > p.second; });

		boneWeights.insert(findIt, Pair(boneIndex, weight));
	}

	asBlendWeight GetBlendWeight() const
	{
		asBlendWeight blendWeight;
		for (size_t i = 0; i < boneWeights.size(); ++i)
		{
			if (i >= 4)
			{
				break; // 최대 4개의 뼈대만 사용
			}

			const auto& pair = boneWeights[i];
			blendWeight.Set(static_cast<uint32>(i), pair.first, pair.second);
		}

		return blendWeight;
	}

	void Normalize()
	{
		if (boneWeights.size() >= 4)
		{
			boneWeights.resize(4);
		}

		float totalWeight = 0.0f;
		for (const auto& pair : boneWeights)
		{
			totalWeight += pair.second;
		}

		float scale = 1.0f / totalWeight;
		for (auto& pair : boneWeights)
		{
			pair.second *= scale;
		}
	}
};

struct asKeyframeData
{
	float time;
	Vec3 scale;
	Quaternion rotation;
	Vec3 translation;
};

struct asKeyframe
{
	std::string boneName;
	std::vector<asKeyframeData> transforms;
};

struct asAnimation
{
	std::string name;
	uint32 frameCount;
	float frameRate;
	float duration;
	std::vector<std::shared_ptr<asKeyframe>> keyframes;
};

// Cache
struct asAnimationNode
{
	std::string name;
	std::vector<asKeyframeData> keyframe;
};