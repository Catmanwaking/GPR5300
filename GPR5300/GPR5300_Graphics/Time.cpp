#include "Time.h"

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
