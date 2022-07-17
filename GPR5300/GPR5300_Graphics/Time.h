#pragma once
#include <d3d9.h>
#include <chrono>
#include "IUpdateable.h"

using namespace std::chrono;

typedef high_resolution_clock HRC;
typedef high_resolution_clock::time_point TimePoint;
typedef duration<FLOAT> Duration;//TODO duration in float

class Time : public IUpdateable
{
public:
	INT Init();
	virtual void Update();
	void DeInit();

	FLOAT GetDeltaTime() { return deltaTime; }

private:
	TimePoint lastTimeStamp;
	FLOAT deltaTime = 0.0f;
};

