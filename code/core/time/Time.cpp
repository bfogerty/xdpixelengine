#include "Time.h"

Time *Time::mpInst = NULL;

#define MS_TO_SEC(ms) ms / 1000.000f;

Time::Time()
{
	mfStartTime = 0.000f;
	mfTime = 0.000f;
	mfDeltaTime = 0.000f;
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
	mfStartTime = static_cast<float>(timeGetTime());
}

void Time::End()
{
	mfDeltaTime = ( timeGetTime() - mfStartTime ) / 1000.0f;
	mfTime += mfDeltaTime;
}

float Time::GetTime()
{
	return mfTime;
}

float Time::GetDeltaTime()
{
	return mfDeltaTime;
}

