#include "pch.h"
#include "Transform.h"

Transform::Transform() : Super(ComponentType::Transform)
{

}

Transform::~Transform()
{

}

void Transform::Awake()
{

}

void Transform::Update()
{
	
}

void Transform::UpdateTransform()
{
	Matrix matScale = Matrix::CreateScale(_localScale);
	Matrix matRotation = Matrix::CreateRotationX(_localRotation.x);
	matRotation *= Matrix::CreateRotationY(_localRotation.y);
	matRotation *= Matrix::CreateRotationZ(_localRotation.z);
	Matrix matTranslation = Matrix::CreateTranslation(_localPosition);

	_matLocal = matScale * matRotation * matTranslation;
	if (HasParent())
	{
		_matWorld = _matLocal * _parent->GetWorldMatrix();
	}
	else
	{
		_matWorld = _matLocal;
	}

	Quaternion rotation;
	_matWorld.Decompose(_scale, rotation, _position);
	_rotation = rotation.ToEuler();

	for (const std::shared_ptr<Transform>& child : _children)
	{
		child->UpdateTransform();
	}
}

void Transform::SetPosition(const Vec3& worldPosition)
{
	if (HasParent())
	{
		Matrix worldToParentLocalMatrix = _parent->GetWorldMatrix().Invert();

		Vec3 position;
		position.Transform(worldPosition, worldToParentLocalMatrix);

		SetLocalPosition(position);
	}
	else
	{
		SetLocalPosition(worldPosition);
	}
}

void Transform::SetRotation(const Vec3& worldRotation)
{
	if (HasParent())
	{
		Matrix worldToParentLocalMatrix = _parent->GetWorldMatrix().Invert();

		Vec3 rotation;
		rotation.TransformNormal(worldRotation, worldToParentLocalMatrix);

		SetLocalRotation(rotation);
	}
	else
	{
		SetLocalRotation(worldRotation);
	}
}

void Transform::SetScale(const Vec3& worldScale)
{
	if (HasParent())
	{
		Vec3 parentScale = _parent->GetScale();
		Vec3 scale = worldScale;
		scale.x /= parentScale.x;
		scale.y /= parentScale.y;
		scale.z /= parentScale.z;
		SetLocalScale(scale);
	}
	else
	{
		SetLocalScale(worldScale);
	}
}

void Transform::SetParent(std::shared_ptr<Transform> parent)
{
	if (parent == nullptr)
	{
		return;
	}

	if (parent == shared_from_this())
	{
		return;
	}

	if (HasParent())
	{
		_parent->RemoveChild(shared_from_this());
	}

	parent->AddChild(shared_from_this());
	_parent = parent;
}

void Transform::AddChild(std::shared_ptr<Transform> child)
{
	if (child == nullptr)
	{
		return;
	}

	if (child->HasParent())
	{
		child->GetParent()->RemoveChild(child);
	}

	child->_parent = shared_from_this();
	_children.push_back(child);
}

void Transform::RemoveChild(std::shared_ptr<Transform> child)
{
	if (child == nullptr)
	{
		return;
	}

	auto it = std::find(_children.begin(), _children.end(), child);
	if (it != _children.end())
	{
		_children.erase(it);
		child->_parent = nullptr;
	}
}
