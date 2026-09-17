#pragma once
#include <glc2d.h>
class Timer
{
private:
	long long _lastTime;
	float _deltaTime;
public:
	Timer();
	~Timer();

	void Init();
	void Update();

	float GetDeltaTime() const;
};

