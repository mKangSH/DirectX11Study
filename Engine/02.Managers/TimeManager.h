#pragma once

class TimeManager
{
	DECLARE_SINGLETON(TimeManager)

public:
	void Init();
	void Update();

	float GetFps() const { return _fps; }
	float GetDeltaTime() const { return _deltaTime; }

private:
	uint64 _frequency = 0;
	uint64 _prevCount = 0;
	float _deltaTime = 0.0f;
	
private:
	uint64 _frameCount = 0;
	float _frameTime = 0.0f;
	float _fps = 0;
};

