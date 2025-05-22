#include "pch.h"
#include "CameraScript.h"

CameraScript::CameraScript()
{
}

CameraScript::~CameraScript()
{
}

void CameraScript::Start()
{
	_cameraTransform = GetTransform();
}

void CameraScript::Update()
{
	float deltaTime = TIME->GetDeltaTime();

	KeyboardScript(deltaTime);
	//MouseScript(deltaTime);
}

void CameraScript::KeyboardScript(const float& deltaTime)
{
	Vec3 pos = _cameraTransform->GetPosition();

	if (INPUT->GetButton(KEY_TYPE::A))
	{
		pos -= _cameraTransform->GetRight() * _speed * deltaTime;
	}

	if (INPUT->GetButton(KEY_TYPE::D))
	{
		pos += _cameraTransform->GetRight() * _speed * deltaTime;
	}

	if (INPUT->GetButton(KEY_TYPE::W))
	{
		pos += _cameraTransform->GetLook() * _speed * deltaTime;
	}

	if (INPUT->GetButton(KEY_TYPE::S))
	{
		pos -= _cameraTransform->GetLook() * _speed * deltaTime;
	}

	_cameraTransform->SetPosition(pos);

	if (INPUT->GetButton(KEY_TYPE::Q))
	{
		Vec3 rotation = _cameraTransform->GetRotation();
		rotation.x += deltaTime * 0.5f;
		_cameraTransform->SetRotation(rotation);
	}

	if (INPUT->GetButton(KEY_TYPE::E))
	{
		Vec3 rotation = _cameraTransform->GetRotation();
		rotation.x -= deltaTime * 0.5f;
		_cameraTransform->SetRotation(rotation);
	}

	if (INPUT->GetButton(KEY_TYPE::C))
	{
		Vec3 rotation = _cameraTransform->GetRotation();
		rotation.y += deltaTime * 0.5f;
		_cameraTransform->SetRotation(rotation);
	}

	if (INPUT->GetButton(KEY_TYPE::Z))
	{
		Vec3 rotation = _cameraTransform->GetRotation();
		rotation.y -= deltaTime * 0.5f;
		_cameraTransform->SetRotation(rotation);
	}
}

void CameraScript::MouseScript(const float& deltaTime)
{
	POINT mousePos = INPUT->GetMousePos();
	Vec2 mouseDelta = Vec2(mousePos.x - _prevMousePos.x, mousePos.y - _prevMousePos.y);

	if (INPUT->GetButton(KEY_TYPE::LBUTTON))
	{
		Vec3 rotation = GetTransform()->GetRotation();
		rotation.x += mouseDelta.y * 0.1f * deltaTime;
		rotation.y += mouseDelta.x * 0.1f * deltaTime;
		GetTransform()->SetRotation(rotation);
	}

	_prevMousePos = mousePos;
}
