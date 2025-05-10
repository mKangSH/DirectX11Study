#pragma once

class Pipeline;
class Transform;
class Component;
class MonoBehaviour;
class Camera;
//class MeshRenderer;
//class Animator;

class SceneObject : public std::enable_shared_from_this<SceneObject>
{
public:
	SceneObject();
	~SceneObject();

	void Awake();
	void Start();
	void Update();
	void LateUpdate();
	void FixedUpdate();

	std::shared_ptr<Component> GetFixedComponent(ComponentType type);
	std::shared_ptr<Transform> GetTransform();
	std::shared_ptr<Camera> GetCamera();
	//std::shared_ptr<MeshRenderer> GetMeshRenderer();
	//std::shared_ptr<Animator> GetAnimator();

	std::shared_ptr<Transform> GetOrAddTransform();
	void AddComponent(std::shared_ptr<Component> component);

protected:
	// 고정 크기 컴포넌트
	std::array<std::shared_ptr<Component>, FIXED_COMPONENT_COUNT> _components;
	// 동적 크기 컴포넌트
	std::vector<std::shared_ptr<MonoBehaviour>> _scripts;
};

