#pragma once
#include "Component.h"

class Transform : public Component, public std::enable_shared_from_this<Transform>
{
	using Super = Component;

public:
	Transform();
	virtual ~Transform();

	virtual void Awake() override;
	virtual void Update() override;

	void UpdateTransform();

	// Local
	Vec3 GetLocalPosition() const { return _localPosition; }
	void SetLocalPosition(const Vec3& position) { _localPosition = position; UpdateTransform(); }
	Vec3 GetLocalRotation() const { return _localRotation; }
	void SetLocalRotation(const Vec3& rotation) { _localRotation = rotation; UpdateTransform(); }
	Vec3 GetLocalScale() const { return _localScale; }
	void SetLocalScale(const Vec3& scale) { _localScale = scale; UpdateTransform(); }

	// World
	Vec3 GetPosition() const { return _position; }
	void SetPosition(const Vec3& worldPosition);
	Vec3 GetRotation() const { return _rotation; }
	void SetRotation(const Vec3& worldRotation);
	Vec3 GetScale() const { return _scale; }
	void SetScale(const Vec3& worldScale);

	Vec3 GetRight() const { return _matWorld.Right(); }
	Vec3 GetUp() const { return _matWorld.Up(); }
	Vec3 GetLook() const { return _matWorld.Backward(); }

	Matrix GetWorldMatrix() const { return _matWorld; }

	// Hierarchy
	bool HasParent() const { return _parent != nullptr; }

	std::shared_ptr<Transform> GetParent() const { return _parent; }
	void SetParent(std::shared_ptr<Transform> parent);

	const std::vector<std::shared_ptr<Transform>>& GetChildren() const { return _children; }
	void AddChild(std::shared_ptr<Transform> child);
	void RemoveChild(std::shared_ptr<Transform> child);

private:
	Vec3 _localPosition = { 0.0f, 0.0f, 0.0f };
	Vec3 _localRotation = { 0.0f, 0.0f, 0.0f };
	Vec3 _localScale = { 1.0f, 1.0f, 1.0f };
	
	// Cache
	Matrix _matLocal = Matrix::Identity;
	Matrix _matWorld = Matrix::Identity;

	Vec3 _scale;
	Vec3 _rotation;
	Vec3 _position;

private:
	std::shared_ptr<Transform> _parent = nullptr;
	std::vector<std::shared_ptr<Transform>> _children = {};
};

