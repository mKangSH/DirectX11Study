#pragma once

enum class KEY_TYPE
{
	UP = VK_UP,
	DOWN = VK_DOWN,
	LEFT = VK_LEFT,
	RIGHT = VK_RIGHT,

	W = 'W',
	A = 'A',
	S = 'S',
	D = 'D',

	Q = 'Q',
	E = 'E',
	Z = 'Z',
	C = 'C',

	KEY_1 = '1',
	KEY_2 = '2',
	KEY_3 = '3',
	KEY_4 = '4',

	LBUTTON = VK_LBUTTON,
	RBUTTON = VK_RBUTTON,
};

enum class KEY_STATE
{
	NONE,
	PRESS,
	DOWN,
	UP,
	END
};

enum
{
	KEY_TYPE_COUNT = static_cast<int32>(UINT8_MAX) + 1,
	KEY_STATE_COUNT = static_cast<int32>(KEY_STATE::END)
};


class InputManager
{
	DECLARE_SINGLETON(InputManager)

public:
	void Init(HWND hwnd);
	void Update();

	bool GetButton(KEY_TYPE key) const { return GetState(key) == KEY_STATE::PRESS; };
	bool GetButtonUp(KEY_TYPE key) const { return GetState(key) == KEY_STATE::UP; };
	bool GetButtonDown(KEY_TYPE key) const { return GetState(key) == KEY_STATE::DOWN; };
	
	const POINT& GetMousePos() const { return _mousePos; }

private:
	inline KEY_STATE GetState(KEY_TYPE key) const
	{
		return _keyState[static_cast<int32>(key)];
	}

private:
	HWND _hwnd = nullptr;

	std::array<KEY_STATE, KEY_TYPE_COUNT> _keyState = {};

	POINT _mousePos = {};
};

