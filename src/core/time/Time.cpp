#include "Time.h"

Time *Time::mpInst = NULL;

#define MS_TO_SEC(ms) ms / 1000.000f;

Time::Time()
{
	mfStartTime = 0.000f;
	mfTime = 0.000f;
	mfDeltaTime = 0.000f;
	fpsTimeCounter = 0.000f;
	fpsCounter = 0;
	fpsDisplayCount = 0;

	tickCount = 0;

	smoothSampleCount = 0;
	sampleDeltaAccum = 0.000f;

	mfSmoothDeltaTime = -1.0f;

	lastTime = 0.0f;
}

Time *Time::GetInstance()
{
	if( mpInst == NULL )
	{
		mpInst = new Time();
	}

	return mpInst;
}

void Time::Start()
{
	//timeBeginPeriod(1);
	//mfStartTime = static_cast<float>(timeGetTime());
	//timeEndPeriod(1);
}

void Time::End()
{
	timeBeginPeriod(1);
	float time = static_cast<float>(timeGetTime());
	timeEndPeriod(1);
	float dt = ( time - lastTime );

	if( dt > 0.00f )
	{
		mfDeltaTime = dt / 1000.0f;
	}

	//char buf[50];
	//sprintf(buf, "t =%f, dt=%f\n", time, time-lastTime);
	//OutputDebugString(buf);

	lastTime = time;

	mfTime += mfDeltaTime;

	fpsTimeCounter += mfDeltaTime;
	if( fpsTimeCounter < 1.0f )
	{
		++fpsCounter;
	}
	else
	{
		fpsTimeCounter = 0.0f;
		fpsDisplayCount = fpsCounter;
		fpsCounter = 0;

		++smoothSampleCount;
		if( smoothSampleCount >= 1 )
		{
			mfSmoothDeltaTime = sampleDeltaAccum / (float)tickCount;
			sampleDeltaAccum = 0.000f;
			smoothSampleCount = 0;
			tickCount = 0;
		}
	}

	sampleDeltaAccum += mfDeltaTime;

	++tickCount;
}

float Time::GetTime()
{
	return mfTime;
}

float Time::GetDeltaTime()
{
	return mfDeltaTime;
}

float Time::GetSmoothDeltaTime()
{
	if( mfSmoothDeltaTime < 0.000f )
	{
		return GetDeltaTime();
	}

	return mfSmoothDeltaTime;
}

int Time::GetFPS()
{
	return fpsDisplayCount;
}