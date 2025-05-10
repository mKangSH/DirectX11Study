#include "pch.h"
#include "Component.h"

Component::Component(ComponentType type) : _type(type)
{
}

Component::~Component()
{
}

std::shared_ptr<SceneObject> Component::GetSceneObject()
{
	return _sceneObject.lock();
}

std::shared_ptr<Transform> Component::GetTransform()
{
	return _sceneObject.lock()->GetTransform();
}
