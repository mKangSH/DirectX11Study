#include "pch.h"
#include "InstancingManager.h"
#include "../03.SceneObject/SceneObject.h"
#include "../04.Component/MeshRenderer.h"
#include "../04.Component/ModelRenderer.h"
#include "../04.Component/ModelAnimator.h"

void InstancingManager::Render(std::vector<std::shared_ptr<SceneObject>>& sceneObjects)
{
	ClearData();

	RenderMeshRenderer(sceneObjects);
}

void InstancingManager::ClearData()
{
	for (auto& pair : _buffers)
	{
		std::shared_ptr<InstancingBuffer>& buffer = pair.second;
		buffer->ClearData();
	}
}

void InstancingManager::RenderMeshRenderer(std::vector<std::shared_ptr<SceneObject>>& sceneObjects)
{
	std::map<InstanceID, std::vector<std::shared_ptr<SceneObject>>> cache;

	// 같은 오브젝트끼리 분류
	for (std::shared_ptr<SceneObject>& sceneObject : sceneObjects)
	{
		if (sceneObject->GetMeshRenderer() == nullptr)
		{
			continue;
		}

		const InstanceID instanceId = sceneObject->GetMeshRenderer()->GetInstanceID();
		cache[instanceId].push_back(sceneObject);
	}

	for (auto& pair : cache)
	{
		const std::vector<std::shared_ptr<SceneObject>>& vec = pair.second;

		/*if (vec.size() == 1)
		{

		}
		else*/
		{
			const InstanceID instanceId = pair.first;

			for (size_t i = 0; i < vec.size(); i++)
			{
				const std::shared_ptr<SceneObject>& sceneObject = vec[i];

				InstancingData data;
				data.world = sceneObject->GetTransform()->GetWorldMatrix();

				AddData(instanceId, data);
			}

			std::shared_ptr<InstancingBuffer>& buffer = _buffers[instanceId];
			vec[0]->GetMeshRenderer()->RenderInstancing(buffer);
		}
	}
}

void InstancingManager::AddData(InstanceID instanceId, InstancingData& data)
{
	if (_buffers.find(instanceId) == _buffers.end())
	{
		_buffers[instanceId] = std::make_shared<InstancingBuffer>();
	}

	_buffers[instanceId]->AddData(data);
}
