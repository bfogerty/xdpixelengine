#ifndef __TIME_MANAGER__
#define __TIME_MANAGER__

#include <windows.h>

class Time
{
private:
	static Time *mpInst;
	float mfTime;
	float mfDeltaTime;

	float mfStartTime;
	float fpsTimeCounter;
	int fpsCounter;
	int fpsDisplayCount;

	Time();


public:
	static Time *GetInstance();

	void Start();
	void End();

	float GetTime();
	float GetDeltaTime();

	int GetFPS();
};

#endif