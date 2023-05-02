#include <PCH.h>
#include <Engine/Timer.h>

Timer::Timer() : deltaTime(0.f)
{
}

Timer::~Timer()
{
}

void Timer::Update()
{
    auto currentTime = std::chrono::system_clock::now();
    auto elapsedSecond = std::chrono::duration<double>();

    if (prevTime.time_since_epoch().count())
    {
        elapsedSecond = currentTime - prevTime;
    }

    prevTime = currentTime;

    deltaTime = (float)elapsedSecond.count();
}
