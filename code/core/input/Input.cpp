#include "Input.h"

Input *Input::mInst = 0;

static Input* Input::Inst()
{
	if( mInst == 0 )
	{
		mInst = new Input();
	}

	return mInst;
}