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

}

void CameraScript::Update()
{
	float deltaTime = TIME->GetDeltaTime();

	Vec3 pos = GetTransform()->GetPosition();

	if (INPUT->GetButton(KEY_TYPE::A))
	{
		pos -= GetTransform()->GetRight() * 3.f * deltaTime;
	}

	if (INPUT->GetButton(KEY_TYPE::D))
	{
		pos += GetTransform()->GetRight() * 3.f * deltaTime;
	}

	if (INPUT->GetButton(KEY_TYPE::W))
	{
		pos += GetTransform()->GetLook() * 3.f * deltaTime;
	}

	if (INPUT->GetButton(KEY_TYPE::S))
	{
		pos -= GetTransform()->GetLook() * 3.f * deltaTime;
	}

	GetTransform()->SetPosition(pos);

	if (INPUT->GetButton(KEY_TYPE::Q))
	{
		Vec3 rotation = GetTransform()->GetRotation();
		rotation.x += deltaTime * 0.5f;
		GetTransform()->SetRotation(rotation);
	}

	if (INPUT->GetButton(KEY_TYPE::E))
	{
		Vec3 rotation = GetTransform()->GetRotation();
		rotation.x -= deltaTime * 0.5f;
		GetTransform()->SetRotation(rotation);
	}

	if (INPUT->GetButton(KEY_TYPE::C))
	{
		Vec3 rotation = GetTransform()->GetRotation();
		rotation.y += deltaTime * 0.5f;
		GetTransform()->SetRotation(rotation);
	}

	if (INPUT->GetButton(KEY_TYPE::Z))
	{
		Vec3 rotation = GetTransform()->GetRotation();
		rotation.y -= deltaTime * 0.5f;
		GetTransform()->SetRotation(rotation);
	}
}
