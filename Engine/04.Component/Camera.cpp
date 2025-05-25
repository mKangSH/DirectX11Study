#include "pch.h"
#include "Camera.h"
#include <chrono>

Matrix Camera::S_MatView = Matrix::Identity;
Matrix Camera::S_MatProjection = Matrix::Identity;

Camera::Camera() : Super(ComponentType::Camera)
{
	_width = GAME->GetGameDesc().width;
	_height = GAME->GetGameDesc().height;
}

Camera::~Camera()
{

}

void Camera::Update()
{
	UpdateMatrix();
}

void Camera::UpdateMatrix()
{
	// View Matrix 备窍绰 规过 1 (10 us)
	// Vec3 eyePosition = GetTransform()->GetPosition();
	// Vec3 focusPosition = eyePosition + GetTransform()->GetLook();
	// Vec3 upDirection = GetTransform()->GetUp();
	// S_MatView = ::XMMatrixLookAtLH(eyePosition, focusPosition, upDirection);

	// View Matrix 备窍绰 规过 2 (3~4 us)
	S_MatView = GetTransform()->GetWorldMatrix().Invert();

	if (_projectionType == ProjectionType::Perspective)
	{
		S_MatProjection = ::XMMatrixPerspectiveFovLH(_fov, _width / _height, _near, _far);
	}
	else
	{
		S_MatProjection = ::XMMatrixOrthographicLH(4.0f, 3.0f, 0.0f, 1.0f);
	}
}
