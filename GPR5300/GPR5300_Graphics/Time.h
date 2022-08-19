#pragma once
#include <d3d11.h>
#include <chrono>
#include "IUpdateable.h"

using namespace std::chrono;

typedef high_resolution_clock HRC;
typedef high_resolution_clock::time_point TimePoint;
typedef duration<FLOAT> Duration;

class Time : public IUpdateable
{
public:
	static Time* GetInstance();

	//Initializes the Time object
	INT Init();
	virtual void Update();
	void DeInit();

	//Returns the time between the last two Update calls.
	FLOAT const GetDeltaTime() { return deltaTime; }

private:
	static Time* instance;

	TimePoint lastTimeStamp;
	FLOAT deltaTime = 0.0f;
};

