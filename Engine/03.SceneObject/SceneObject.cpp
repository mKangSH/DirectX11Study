#include "pch.h"
#include "SceneObject.h"
#include "../04.Component/Component.h"
#include "../04.Component/MonoBehaviour.h"
#include "../04.Component/Camera.h"
#include "../04.Component/MeshRenderer.h"
//#include "../04.Component/Animation/Animator.h"
#include "../04.Component/ModelRenderer.h"

SceneObject::SceneObject()
{
	
}

SceneObject::~SceneObject()
{
}

void SceneObject::Awake()
{
	for (std::shared_ptr<Component>& component : _components)
	{
		if (component == nullptr)
		{
			continue;
		}

		component->Awake();
	}

	for (std::shared_ptr<MonoBehaviour>& script : _scripts)
	{
		script->Awake();
	}
}

void SceneObject::Start()
{
	for (std::shared_ptr<Component>& component : _components)
	{
		if (component == nullptr)
		{
			continue;
		}

		component->Start();
	}

	for (std::shared_ptr<MonoBehaviour>& script : _scripts)
	{
		script->Start();
	}
}

void SceneObject::Update()
{
	for (std::shared_ptr<Component>& component : _components)
	{
		if (component == nullptr)
		{
			continue;
		}

		component->Update();
	}

	for (std::shared_ptr<MonoBehaviour>& script : _scripts)
	{
		script->Update();
	}
}

void SceneObject::LateUpdate()
{
	for (std::shared_ptr<Component>& component : _components)
	{
		if (component == nullptr)
		{
			continue;
		}

		component->LateUpdate();
	}

	for (std::shared_ptr<MonoBehaviour>& script : _scripts)
	{
		script->LateUpdate();
	}
}

void SceneObject::FixedUpdate()
{
	for (std::shared_ptr<Component>& component : _components)
	{
		if (component == nullptr)
		{
			continue;
		}

		component->FixedUpdate();
	}

	for (std::shared_ptr<MonoBehaviour>& script : _scripts)
	{
		script->FixedUpdate();
	}
}

std::shared_ptr<Component> SceneObject::GetFixedComponent(ComponentType type)
{
	uint8 index = static_cast<uint8>(type);
	assert(index < FIXED_COMPONENT_COUNT);
	return _components[index];
}

std::shared_ptr<Transform> SceneObject::GetTransform()
{
	std::shared_ptr<Component> component = GetFixedComponent(ComponentType::Transform);
	return std::static_pointer_cast<Transform>(component);
}

std::shared_ptr<Camera> SceneObject::GetCamera()
{
	std::shared_ptr<Component> component = GetFixedComponent(ComponentType::Camera);
	return std::static_pointer_cast<Camera>(component);
}

std::shared_ptr<MeshRenderer> SceneObject::GetMeshRenderer()
{
	std::shared_ptr<Component> component = GetFixedComponent(ComponentType::MeshRenderer);
	return std::static_pointer_cast<MeshRenderer>(component);
}

std::shared_ptr<ModelRenderer> SceneObject::GetModelRenderer()
{
	std::shared_ptr<Component> component = GetFixedComponent(ComponentType::ModelRenderer);
	return std::static_pointer_cast<ModelRenderer>(component);
}
 
//std::shared_ptr<Animator> SceneObject::GetAnimator()
//{
//	std::shared_ptr<Component> component = GetFixedComponent(ComponentType::Animator);
//	return std::static_pointer_cast<Animator>(component);
//}

std::shared_ptr<Transform> SceneObject::GetOrAddTransform()
{
	if (GetTransform() == nullptr)
	{
		std::shared_ptr<Transform> transform = std::make_shared<Transform>();
		AddComponent(transform);
	}

	return GetTransform();
}

void SceneObject::AddComponent(std::shared_ptr<Component> component)
{
	component->SetGameObject(shared_from_this());

	uint8 index = static_cast<uint8>(component->GetType());
	if (index < FIXED_COMPONENT_COUNT)
	{
		_components[index] = component;
	}
	else
	{
		_scripts.push_back(std::static_pointer_cast<MonoBehaviour>(component));
	}
}