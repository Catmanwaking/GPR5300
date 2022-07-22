#include "Time.h"

Time* Time::instance = nullptr;

Time* Time::GetInstance()
{
    if (instance == nullptr)
    {
        instance = new Time;
    }
    return instance;
}

INT Time::Init()
{
    lastTimeStamp = HRC::now();
    return 0;
}

void Time::Update()
{
    TimePoint now = HRC::now();
    Duration duration = now - lastTimeStamp;
    deltaTime = duration.count();
    lastTimeStamp = now;

}

void Time::DeInit()
{
}
