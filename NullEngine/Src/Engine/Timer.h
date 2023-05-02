#pragma once
#include <Core/Singleton.h>
#include <chrono>
class Timer : public Singleton<Timer>
{
public:
	Timer();
	~Timer();
	void Update();
	float deltaTime;

private:
	std::chrono::system_clock::time_point prevTime;
	float lastUpdate;
};

