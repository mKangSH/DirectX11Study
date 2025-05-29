#include "pch.h"
#include "Converter.h"
#include "../Main/AsTypes.h"
#include <filesystem>
#include <98.Utils/Utils.h>
#include <98.Utils/tinyxml2.h>
#include <98.Utils/FileUtils.h>

Converter::Converter()
{
	_importer = std::make_shared<Assimp::Importer>();
}

Converter::~Converter()
{

}

void Converter::ReadAssetFile(const std::wstring& path)
{
	using namespace std;
	wstring fileString = _assetPath + path;

	// Check if the file exists
	auto systemPath = filesystem::path(fileString);
	assert(filesystem::exists(systemPath));

	_scene = _importer->ReadFile(
		Utils::ToString(systemPath), 
		aiProcess_ConvertToLeftHanded | 
		aiProcess_Triangulate | 
		aiProcess_GenUVCoords | 
		aiProcess_GenNormals | 
		aiProcess_CalcTangentSpace
	);

	assert(_scene != nullptr);
}

void Converter::ExportModelData(const std::wstring& savePath)
{
	using namespace std;

	wstring finalPath = _modelPath + savePath + L".mesh";
	ReadModelData(_scene->mRootNode, -1, -1);
	ReadSkinData();

	//Write CSV File
	{
		FILE* file;
		::fopen_s(&file, "../Vertices.csv", "w");

		for (shared_ptr<asBone>& bone : _bones)
		{
			string name = bone->name;
			::fprintf(file, "%d,%s\n", bone->index, bone->name.c_str());
		}

		::fprintf(file, "\n");

		for (shared_ptr<asMesh>& mesh : _meshes)
		{
			string name = mesh->name;
			::printf("%s\n", name.c_str());

			for (UINT i = 0; i < mesh->vertices.size(); i++)
			{
				Vec3 p = mesh->vertices[i].position;
				Vec4 indices = mesh->vertices[i].blendIndices;
				Vec4 weights = mesh->vertices[i].blendWeights;

				::fprintf(file, "%f,%f,%f,", p.x, p.y, p.z);
				::fprintf(file, "%f,%f,%f,%f,", indices.x, indices.y, indices.z, indices.w);
				::fprintf(file, "%f,%f,%f,%f\n", weights.x, weights.y, weights.z, weights.w);
			}
		}

		::fclose(file);
	}


	WriteModelFile(finalPath);
}

void Converter::ExportMaterialData(const std::wstring& savePath)
{
	std::wstring finalPath = _texturePath + savePath + L".xml";
	ReadMaterialData();
	WriteMaterialData(finalPath);
}

void Converter::ExportAnimationData(const std::wstring& savePath, uint32 index)
{
	std::wstring finalPath = _modelPath + savePath + L".clip";
	assert(index < _scene->mNumAnimations);

	std::shared_ptr<asAnimation> animation = ReadAnimationData(_scene->mAnimations[index]);
	WriteAnimationFile(animation, finalPath);
}

void Converter::ReadModelData(aiNode* node, int32 index, int32 parentIndex)
{
	std::shared_ptr<asBone> bone = std::make_shared<asBone>();
	bone->index = index;
	bone->parentIndex = parentIndex;
	bone->name = node->mName.C_Str();

	// 4x4 Matrix
	// fbx인 경우 Transpose가 필요
	Matrix transform(node->mTransformation[0]);
	bone->transform = transform.Transpose();

	Matrix matParent = Matrix::Identity;
	if (parentIndex >= 0)
	{
		matParent = _bones[parentIndex]->transform;
	}

	// Local (Root) Transform
	bone->transform = bone->transform * matParent;
	_bones.push_back(bone);

	// Mesh
	ReadMeshData(node, index);

	for (uint32 i = 0; i < node->mNumChildren; i++)
	{
		aiNode* childNode = node->mChildren[i];
		ReadModelData(childNode, _bones.size(), index);
	}
}

void Converter::ReadMeshData(aiNode* node, int32 bone)
{
	if (node->mNumMeshes < 1)
	{
		return;
	}

	std::shared_ptr<asMesh> mesh = std::make_shared<asMesh>();
	mesh->name = node->mName.C_Str();
	mesh->boneIndex = bone;

	for (uint32 i = 0; i < node->mNumMeshes; i++)
	{
		uint32 meshIndex = node->mMeshes[i];
		const aiMesh* srcMesh = _scene->mMeshes[meshIndex];

		const aiMaterial* srcMaterial = _scene->mMaterials[srcMesh->mMaterialIndex];
		mesh->materialName = srcMaterial->GetName().C_Str();

		// 이전 vertex 개수
		const uint32 startVertex = mesh->vertices.size();
		mesh->vertices.reserve(startVertex + srcMesh->mNumVertices + 1);
		for (uint32 v = 0; v < srcMesh->mNumVertices; v++)
		{
			// Vertex
			VertexType vertex;
			::memcpy(&vertex.position, &srcMesh->mVertices[v], sizeof(Vec3));

			// UV
			if (srcMesh->HasTextureCoords(0))
			{
				::memcpy(&vertex.uv, &srcMesh->mTextureCoords[0][v], sizeof(Vec2));
			}
			
			// Normal
			if (srcMesh->HasNormals())
			{
				::memcpy(&vertex.normal, &srcMesh->mNormals[v], sizeof(Vec3));
			}
			
			mesh->vertices.push_back(vertex);
		}

		// Index
		for (uint32 f = 0; f < srcMesh->mNumFaces; f++)
		{
			aiFace& face = srcMesh->mFaces[f];

			for (uint32 k = 0; k < face.mNumIndices; k++)
				mesh->indices.push_back(face.mIndices[k] + startVertex);
		}
	}

	_meshes.push_back(mesh);
}

void Converter::ReadSkinData()
{
	using namespace std;
	for (uint32 i = 0; i < _scene->mNumMeshes; i++)
	{
		const aiMesh* srcMesh = _scene->mMeshes[i];
		if (srcMesh->HasBones() == false)
		{
			continue;
		}

		shared_ptr<asMesh> mesh = _meshes[i];

		vector<asBoneWeights> tempVertexBoneWeights;
		tempVertexBoneWeights.resize(mesh->vertices.size());

		// Bone을 순회하면서 VertexId, Weight를 찾아서 기록
		for (uint32 j = 0; j < srcMesh->mNumBones; j++)
		{
			const aiBone* srcMeshBone = srcMesh->mBones[j];
			uint32 boneIndex = GetBoneIndex(srcMeshBone->mName.C_Str());

			for(uint32 w = 0; w < srcMeshBone->mNumWeights; w++)
			{
				uint32 index = srcMeshBone->mWeights[w].mVertexId;
				float weight = srcMeshBone->mWeights[w].mWeight;
				tempVertexBoneWeights[index].AddWeights(boneIndex, weight);
			}
		}

		// 최종 결과 계산
		for (uint32 v = 0; v < tempVertexBoneWeights.size(); v++)
		{
			tempVertexBoneWeights[v].Normalize();

			asBlendWeight blendWeight = tempVertexBoneWeights[v].GetBlendWeight();
			mesh->vertices[v].blendIndices = blendWeight.indices;
			mesh->vertices[v].blendWeights = blendWeight.weights;
		}
	}
}

void Converter::WriteModelFile(std::wstring finalPath)
{
	using namespace std;
	
	filesystem::path path = filesystem::path(finalPath);
	if (filesystem::exists(path.parent_path()) == false)
	{
		filesystem::create_directory(path.parent_path());
	}

	shared_ptr<FileUtils> file = make_shared<FileUtils>();
	file->Open(finalPath, FileMode::Write);

	// Bone Data
	file->Write<uint32>(_bones.size());
	for (shared_ptr<asBone>& bone : _bones)
	{
		file->Write<int32>(bone->index);
		file->Write<string>(bone->name);
		file->Write<int32>(bone->parentIndex);
		file->Write<Matrix>(bone->transform);
	}

	// Mesh Data
	file->Write<uint32>(_meshes.size());
	for (shared_ptr<asMesh>& meshData : _meshes)
	{
		file->Write<string>(meshData->name);
		file->Write<int32>(meshData->boneIndex);
		file->Write<string>(meshData->materialName);

		// Vertex Data
		file->Write<uint32>(meshData->vertices.size());
		file->Write(&meshData->vertices[0], sizeof(VertexType) * meshData->vertices.size());

		// Index Data
		file->Write<uint32>(meshData->indices.size());
		file->Write(&meshData->indices[0], sizeof(uint32) * meshData->indices.size());
	}
}

std::shared_ptr<asAnimation> Converter::ReadAnimationData(const aiAnimation* srcAnimation)
{
	std::shared_ptr<asAnimation> animation = std::make_shared<asAnimation>();
	animation->name = srcAnimation->mName.C_Str();
	animation->frameRate = static_cast<float>(srcAnimation->mTicksPerSecond);
	animation->frameCount = static_cast<uint32>(srcAnimation->mDuration + 1);

	std::map<std::string, std::shared_ptr<asAnimationNode>> cacheAnimNode;

	for(uint32 i = 0; i < srcAnimation->mNumChannels; i++)
	{
		aiNodeAnim* srcNode = srcAnimation->mChannels[i];

		// Animation Node Parsing
		std::shared_ptr<asAnimationNode> node = ParseAnimationNode(animation, srcNode);

		animation->duration = max(animation->duration, node->keyframe.back().time);

		cacheAnimNode[srcNode->mNodeName.C_Str()] = node;
	}

	ReadKeyframeData(animation, _scene->mRootNode, cacheAnimNode);

	return animation;
}

std::shared_ptr<asAnimationNode> Converter::ParseAnimationNode(std::shared_ptr<asAnimation> animation, aiNodeAnim* srcNode)
{
	std::shared_ptr<asAnimationNode> node = std::make_shared<asAnimationNode>();
	node->name = srcNode->mNodeName.C_Str();
	
	uint32 keyCount = max(max(srcNode->mNumPositionKeys, srcNode->mNumScalingKeys), srcNode->mNumRotationKeys);
	for(uint32 k = 0; k < keyCount; k++)
	{
		asKeyframeData frameData;

		bool found = false;
		uint32 t = node->keyframe.size();

		// Position
		if (::fabsf(static_cast<float>(srcNode->mPositionKeys[k].mTime) - static_cast<float>(t)) <= 0.0001f)
		{
			aiVectorKey key = srcNode->mPositionKeys[k];
			frameData.time = static_cast<float>(key.mTime);
			::memcpy_s(&frameData.translation, sizeof(Vec3), &key.mValue, sizeof(aiVector3D));

			found = true;
		}

		// Rotation
		if (::fabsf(static_cast<float>(srcNode->mRotationKeys[k].mTime) - static_cast<float>(t)) <= 0.0001f)
		{
			aiQuatKey key = srcNode->mRotationKeys[k];
			frameData.time = static_cast<float>(key.mTime);

			frameData.rotation.x = key.mValue.x;
			frameData.rotation.y = key.mValue.y;
			frameData.rotation.z = key.mValue.z;
			frameData.rotation.w = key.mValue.w;

			found = true;
		}

		// Scaling
		if (::fabsf(static_cast<float>(srcNode->mScalingKeys[k].mTime) - static_cast<float>(t)) <= 0.0001f)
		{
			aiVectorKey key = srcNode->mScalingKeys[k];
			frameData.time = static_cast<float>(key.mTime);
			::memcpy_s(&frameData.scale, sizeof(Vec3), &key.mValue, sizeof(aiVector3D));

			found = true;
		}

		if (found)
		{
			node->keyframe.push_back(frameData);
		}
	}

	if (node->keyframe.size() < animation->frameCount)
	{
		// Fill the rest of the keyframes with the last frame data
		asKeyframeData lastFrame = node->keyframe.back();
		for (uint32 t = node->keyframe.size(); t < animation->frameCount; t++)
		{
			node->keyframe.push_back(lastFrame);
			node->keyframe.back().time = static_cast<float>(t);
		}
	}

	return node;
}

void Converter::ReadKeyframeData(std::shared_ptr<asAnimation> animation, aiNode* srcNode, std::map<std::string, std::shared_ptr<asAnimationNode>>& cache)
{
	std::shared_ptr<asKeyframe> keyframe = std::make_shared<asKeyframe>();
	keyframe->boneName = srcNode->mName.C_Str();

	std::shared_ptr<asAnimationNode> findNode = cache[srcNode->mName.C_Str()];
	keyframe->transforms.reserve(animation->frameCount);

	for(uint32 i = 0; i < animation->frameCount; i++)
	{
		asKeyframeData frameData;
		frameData.time = static_cast<float>(i);
		if (findNode)
		{
			frameData = findNode->keyframe[i];
		}
		else
		{
			Matrix transform(srcNode->mTransformation[0]);
			transform = transform.Transpose(); // Assimp uses right-handed, we need left-handed
			frameData.time = static_cast<float>(i);
			transform.Decompose(OUT frameData.scale, OUT frameData.rotation, OUT frameData.translation);
		}

		keyframe->transforms.push_back(frameData);
	}

	animation->keyframes.push_back(keyframe);

	for (uint32 i = 0; i < srcNode->mNumChildren; i++)
	{
		aiNode* childNode = srcNode->mChildren[i];
		ReadKeyframeData(animation, childNode, cache);
	}
}

void Converter::WriteAnimationFile(std::shared_ptr<asAnimation> animation, std::wstring finalPath)
{
	using namespace std;

	filesystem::path path = filesystem::path(finalPath);
	if (filesystem::exists(path.parent_path()) == false)
	{
		filesystem::create_directory(path.parent_path());
	}

	shared_ptr<FileUtils> file = make_shared<FileUtils>();
	file->Open(finalPath, FileMode::Write);

	// Bone Data
	file->Write<std::string>(animation->name);
	file->Write<float>(animation->duration);
	file->Write<float>(animation->frameRate);
	file->Write<uint32>(animation->frameCount);

	file->Write<uint32>(animation->keyframes.size());

	for (const shared_ptr<asKeyframe>& keyframe : animation->keyframes)
	{
		file->Write<std::string>(keyframe->boneName);
		file->Write<uint32>(keyframe->transforms.size());
		file->Write(keyframe->transforms.data(), sizeof(asKeyframeData) * keyframe->transforms.size());
	}
}

void Converter::ReadMaterialData()
{
	for (uint32 i = 0; i < _scene->mNumMaterials; i++)
	{
		aiMaterial* srcMaterial = _scene->mMaterials[i];

		std::shared_ptr<asMaterial> material = std::make_shared<asMaterial>();
		material->name = srcMaterial->GetName().C_Str();

		aiColor3D color;

		// Ambient Color
		srcMaterial->Get(AI_MATKEY_COLOR_AMBIENT, color);
		material->ambient = Vec4(color.r, color.g, color.b, 1.0f);

		// Diffuse Color
		srcMaterial->Get(AI_MATKEY_COLOR_DIFFUSE, color);
		material->diffuse = Vec4(color.r, color.g, color.b, 1.0f);

		// Ambient Color
		srcMaterial->Get(AI_MATKEY_COLOR_SPECULAR, color);
		material->specular = Vec4(color.r, color.g, color.b, 1.0f);
		srcMaterial->Get(AI_MATKEY_SHININESS, material->specular.w);

		// Ambient Color
		srcMaterial->Get(AI_MATKEY_COLOR_AMBIENT, color);
		material->ambient = Vec4(color.r, color.g, color.b, 1.0f);

		aiString file;

		// Diffuse Texture
		srcMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &file);
		if (file.length > 0)
		{
			material->diffuseFile = file.C_Str();
		}

		// Specular Texture
		srcMaterial->GetTexture(aiTextureType_SPECULAR, 0, &file);
		if (file.length > 0)
		{
			material->specularFile = file.C_Str();
		}

		// Normal Texture
		srcMaterial->GetTexture(aiTextureType_NORMALS, 0, &file);
		if (file.length > 0)
		{
			material->normalFile = file.C_Str();
		}

		_materials.push_back(material);
	}
}

void Converter::WriteMaterialData(std::wstring finalPath)
{
	using namespace std;

	filesystem::path path = filesystem::path(finalPath);
	if (filesystem::exists(path.parent_path()) == false)
	{
		filesystem::create_directory(path.parent_path());
	}

	string folder = path.parent_path().string();

	shared_ptr<tinyxml2::XMLDocument> document = make_shared<tinyxml2::XMLDocument>();

	tinyxml2::XMLDeclaration* decl = document->NewDeclaration();
	document->LinkEndChild(decl);

	tinyxml2::XMLElement* root = document->NewElement("Materials");
	document->LinkEndChild(root);

	for (auto& material : _materials)
	{
		tinyxml2::XMLElement* node = document->NewElement("Material");
		root->LinkEndChild(node);

		tinyxml2::XMLElement* element = document->NewElement("Name");
		element->SetText(material->name.c_str());
		node->LinkEndChild(element);

		element = document->NewElement("DiffuseFile");
		element->SetText(WriteTexture(folder, material->diffuseFile).c_str());
		node->LinkEndChild(element);

		element = document->NewElement("SpecularFile");
		element->SetText(WriteTexture(folder, material->specularFile).c_str());
		node->LinkEndChild(element);

		element = document->NewElement("NormalFile");
		element->SetText(WriteTexture(folder, material->normalFile).c_str());
		node->LinkEndChild(element);

		element = document->NewElement("Ambient");
		element->SetAttribute("R", material->ambient.x);
		element->SetAttribute("G", material->ambient.y);
		element->SetAttribute("B", material->ambient.z);
		element->SetAttribute("A", material->ambient.w);
		node->LinkEndChild(element);

		element = document->NewElement("Diffuse");
		element->SetAttribute("R", material->diffuse.x);
		element->SetAttribute("G", material->diffuse.y);
		element->SetAttribute("B", material->diffuse.z);
		element->SetAttribute("A", material->diffuse.w);
		node->LinkEndChild(element);

		element = document->NewElement("Specular");
		element->SetAttribute("R", material->specular.x);
		element->SetAttribute("G", material->specular.y);
		element->SetAttribute("B", material->specular.z);
		element->SetAttribute("A", material->specular.w);
		node->LinkEndChild(element);

		element = document->NewElement("Emissive");
		element->SetAttribute("R", material->emissive.x);
		element->SetAttribute("G", material->emissive.y);
		element->SetAttribute("B", material->emissive.z);
		element->SetAttribute("A", material->emissive.w);
		node->LinkEndChild(element);
	}

	document->SaveFile(Utils::ToString(finalPath).c_str());
}

std::string Converter::WriteTexture(std::string saveFolder, std::string file)
{
	using namespace std;

	string fileName = filesystem::path(file).filename().string();
	string folderName = filesystem::path(file).parent_path().string();

	const aiTexture* srcTexture = _scene->GetEmbeddedTexture(file.c_str());
	if (srcTexture)
	{
		string pathStr = (filesystem::path(saveFolder) / fileName).string();
		
		if (srcTexture->mHeight == 0)
		{
			shared_ptr<FileUtils> file = make_shared<FileUtils>();
			file->Open(Utils::ToWString(pathStr), FileMode::Write);
			file->Write(srcTexture->pcData, srcTexture->mWidth);
		}
		else
		{
			D3D11_TEXTURE2D_DESC desc;
			ZeroMemory(&desc, sizeof(desc));
			desc.Width = srcTexture->mWidth;
			desc.Height = srcTexture->mHeight;
			desc.MipLevels = 1;
			desc.ArraySize = 1;
			desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
			desc.SampleDesc.Count = 1;
			desc.SampleDesc.Quality = 0;
			desc.Usage = D3D11_USAGE_IMMUTABLE;

			D3D11_SUBRESOURCE_DATA subResource;
			ZeroMemory(&subResource, sizeof(subResource));
			subResource.pSysMem = srcTexture->pcData;
			
			ComPtr<ID3D11Texture2D> texture;
			HRESULT hr = DEVICE->CreateTexture2D(&desc, &subResource, texture.GetAddressOf());
			assert(SUCCEEDED(hr));

			DirectX::ScratchImage image;
			::CaptureTexture(DEVICE.Get(), DEVICECONTEXT.Get(), texture.Get(), image);

			// Save To File
			hr = DirectX::SaveToDDSFile(*image.GetImages(), DirectX::DDS_FLAGS_NONE, Utils::ToWString(fileName).c_str());
			assert(SUCCEEDED(hr));
		}
	}
	else
	{
		string originalPath = (filesystem::path(_assetPath) / filesystem::path(saveFolder).filename() / file).string();
		Utils::Replace(OUT originalPath, "\\", "/");

		string pathStr = (filesystem::path(saveFolder) / fileName).string();
		Utils::Replace(OUT pathStr, "\\", "/");

		::CopyFileA(originalPath.c_str(), pathStr.c_str(), false);
	}

	return fileName;
}

uint32 Converter::GetBoneIndex(const std::string& name) const
{
	for(std::shared_ptr<asBone> bone : _bones)
	{
		if (bone->name == name)
		{
			return bone->index;
		}
	}

	assert(false);
}
