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

	if (ImGui::IsKeyDown(ImGuiKey::ImGuiKey_A))
	{
		pos -= _cameraTransform->GetRight() * 3.f * deltaTime;
	}

	if (ImGui::IsKeyDown(ImGuiKey::ImGuiKey_D))
	{
		pos += _cameraTransform->GetRight() * 3.f * deltaTime;
	}

	if (ImGui::IsKeyDown(ImGuiKey::ImGuiKey_W))
	{
		pos += _cameraTransform->GetLook() * 3.f * deltaTime;
	}

	if (ImGui::IsKeyDown(ImGuiKey::ImGuiKey_S))
	{
		pos -= _cameraTransform->GetLook() * 3.f * deltaTime;
	}

	_cameraTransform->SetPosition(pos);

	if (ImGui::IsKeyDown(ImGuiKey::ImGuiKey_Q))
	{
		Vec3 rotation = _cameraTransform->GetRotation();
		rotation.x += deltaTime * 0.5f;
		_cameraTransform->SetRotation(rotation);
	}

	if (ImGui::IsKeyDown(ImGuiKey::ImGuiKey_E))
	{
		Vec3 rotation = _cameraTransform->GetRotation();
		rotation.x -= deltaTime * 0.5f;
		_cameraTransform->SetRotation(rotation);
	}

	if (ImGui::IsKeyDown(ImGuiKey::ImGuiKey_C))
	{
		Vec3 rotation = _cameraTransform->GetRotation();
		rotation.y += deltaTime * 0.5f;
		_cameraTransform->SetRotation(rotation);
	}

	if (ImGui::IsKeyDown(ImGuiKey::ImGuiKey_Z))
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
		rotation.y += mouseDelta.x * 0.05f * deltaTime;
		GetTransform()->SetRotation(rotation);
	}

	_prevMousePos = mousePos;
}
