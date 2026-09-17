#include "Timer.h"

Timer::Timer() : _lastTime(0), _deltaTime(0.0f) {}

Timer::~Timer(){}

void Timer::Init()
{
	_lastTime = g2_TimeGetTime();
}

void Timer::Update()
{
	long long curTime = g2_TimeGetTime();

	_deltaTime = static_cast<float>(curTime - _lastTime) / 1000.0f;

	_lastTime = curTime;
}