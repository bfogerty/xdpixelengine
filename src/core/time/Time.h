#ifndef __TIME_MANAGER__
#define __TIME_MANAGER__

#include <windows.h>

class Time
{
private:
	static Time *mpInst;
	float mfTime;
	float mfDeltaTime;
	float mfSmoothDeltaTime;

	float mfStartTime;
	float fpsTimeCounter;
	float lastTime;
	int fpsCounter;
	int fpsDisplayCount;

	int tickCount;
	int smoothSampleCount;
	float sampleDeltaAccum;

	Time();


public:
	static Time *GetInstance();

	void Start();
	void End();

	float GetTime();
	float GetDeltaTime();
	float GetSmoothDeltaTime();

	int GetFPS();
};

#endif