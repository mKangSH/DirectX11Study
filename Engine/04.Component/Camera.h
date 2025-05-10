#pragma once
#include "Component.h"

enum class ProjectionType
{
	Perspective,
	Orthographic,
};

class Camera : public Component
{
	using Super = Component;

public:
	Camera();
	virtual ~Camera();

	virtual void Update() override;

	void SetProjectionType(ProjectionType type) { _projectionType = type; }
	void SetNear(float value) { _near = value; }
	void SetFar(float value) { _far = value; }
	void SetFov(float value) { _fov = value; }
	void SetWidth(float value) { _width = value; }
	void SetHeight(float value) { _height = value; }

	ProjectionType GetProjectionType() const { return _projectionType; }

	void UpdateMatrix();

private:
	ProjectionType _projectionType = ProjectionType::Perspective;

	Matrix _matView = Matrix::Identity;
	Matrix _matProjection = Matrix::Identity;

	float _near = 1.0f;
	float _far = 1000.0f;
	float _fov = XM_PI / 4.0f;
	float _width = 0.0f;
	float _height = 0.0f;

public:
	static Matrix S_MatView;
	static Matrix S_MatProjection;
};

