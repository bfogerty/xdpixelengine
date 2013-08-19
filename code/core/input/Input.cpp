#include "Input.h"


Input *Input::mInst = 0;

Input* Input::Inst()
{
	if( mInst == 0 )
	{
		mInst = new Input();
	}

	return mInst;
}

void Input::Initialize()
{
#ifdef WIN_RELEASE
	mapKeyCodes[KeyCode::LeftArrow] = VK_LEFT;
	mapKeyCodes[KeyCode::RightArrow] = VK_RIGHT;
	mapKeyCodes[KeyCode::UpArrow] = VK_UP;
	mapKeyCodes[KeyCode::DownArrow] = VK_DOWN;
	mapKeyCodes[KeyCode::W] = 'W';
	mapKeyCodes[KeyCode::A] = 'A';
	mapKeyCodes[KeyCode::S] = 'S';
	mapKeyCodes[KeyCode::D] = 'D';
#endif
}

bool Input::GeyKey( int key )
{
#ifdef WIN_RELEASE

	//return GetAsyncKeyState( VK_LEFT ) & 0x8000 != 0 ? TRUE : FALSE;
	return GetAsyncKeyState( mapKeyCodes[key] ) != 0 ? TRUE : FALSE;
#endif

	return FALSE;
}