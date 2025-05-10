#pragma once

class SceneObject;
class Transform;

class Component
{
public:
	explicit Component(ComponentType type);
	virtual ~Component();

	virtual void Awake() {};
	virtual void Start() {};
	virtual void Update() {};
	virtual void LateUpdate() {};
	virtual void FixedUpdate() {};

public:
	ComponentType GetType() const { return _type; }

	std::shared_ptr<SceneObject> GetSceneObject();
	std::shared_ptr<Transform> GetTransform();

private:
	friend class SceneObject;
	void SetGameObject(std::shared_ptr<SceneObject> owner) { _sceneObject = owner; }

protected:
	ComponentType _type;
	std::weak_ptr<SceneObject> _sceneObject;
};

