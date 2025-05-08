#include "pch.h"
#include "InputManager.h"

void InputManager::Init(HWND hwnd)
{
	_hwnd = hwnd;
}

void InputManager::Update()
{
	HWND hwnd = ::GetActiveWindow();
	if (hwnd != _hwnd)
	{
		for (uint32 key = 0; key < KEY_TYPE_COUNT; ++key)
		{
			_keyState[key] = KEY_STATE::NONE;
		}

		return;
	}

	BYTE asciiKeyState[KEY_TYPE_COUNT] = {};
	if (::GetKeyboardState(asciiKeyState) == FALSE)
	{
		return;
	}

	for (uint32 key = 0; key < KEY_TYPE_COUNT; ++key)
	{
		if (asciiKeyState[key] & 0x80)
		{
			KEY_STATE& keyState = _keyState[key];

			if (keyState == KEY_STATE::PRESS || keyState == KEY_STATE::DOWN)
			{
				keyState = KEY_STATE::PRESS;
			}
			else
			{
				keyState = KEY_STATE::DOWN;
			}
		}
		else
		{
			KEY_STATE& keyState = _keyState[key];

			if (_keyState[key] == KEY_STATE::PRESS || keyState == KEY_STATE::DOWN)
			{
				_keyState[key] = KEY_STATE::UP;
			}
			else
			{
				_keyState[key] = KEY_STATE::NONE;
			}
		}

		::GetCursorPos(&_mousePos);
		::ScreenToClient(_hwnd, &_mousePos);
	}
}
