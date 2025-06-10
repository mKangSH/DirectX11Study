#pragma once
#include "../01.Graphics/Buffer/InstancingBuffer.h"

class SceneObject;

class InstancingManager
{
	DECLARE_SINGLETON(InstancingManager)

public:
	void Render(std::vector<std::shared_ptr<SceneObject>>& sceneObjects);
	void ClearData();

private:
	void RenderMeshRenderer(std::vector<std::shared_ptr<SceneObject>>& sceneObjects);

private:
	void AddData(InstanceID instanceId, InstancingData& data);

private:
	std::map<InstanceID, std::shared_ptr<InstancingBuffer>> _buffers;
};

