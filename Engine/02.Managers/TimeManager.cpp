#include "pch.h"
#include "TimeManager.h"

void TimeManager::Init()
{
	::QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*>(&_frequency));
	::QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&_prevCount));
}

void TimeManager::Update()
{
	uint64 currentCount = 0;
	::QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&currentCount));

	_deltaTime = static_cast<float>(currentCount - _prevCount) / static_cast<float>(_frequency);
	_prevCount = currentCount;

	++_frameCount;
	_frameTime += _deltaTime;
	
	if (_frameTime >= 1.0f)
	{
		_fps = static_cast<uint64>(_frameCount / _frameTime);

		_frameTime = 0.0f;
		_frameCount = 0;
	}

	// Set Window Title
	std::wstring fps = GAME->GetGameDesc().appName + L" FPS : " + std::to_wstring(_fps);
	SetWindowText(GAME->GetGameDesc().hWnd, fps.c_str());
}
