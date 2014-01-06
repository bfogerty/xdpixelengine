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

	mapKeyCodes[KeyCode::A] = 'A';
	mapKeyCodes[KeyCode::B] = 'B';
	mapKeyCodes[KeyCode::C] = 'C';
	mapKeyCodes[KeyCode::D] = 'D';
	mapKeyCodes[KeyCode::E] = 'E';
	mapKeyCodes[KeyCode::F] = 'F';
	mapKeyCodes[KeyCode::G] = 'G';
	mapKeyCodes[KeyCode::H] = 'H';
	mapKeyCodes[KeyCode::I] = 'I';
	mapKeyCodes[KeyCode::J] = 'J';
	mapKeyCodes[KeyCode::K] = 'K';
	mapKeyCodes[KeyCode::L] = 'L';
	mapKeyCodes[KeyCode::M] = 'M';
	mapKeyCodes[KeyCode::N] = 'N';
	mapKeyCodes[KeyCode::O] = 'O';
	mapKeyCodes[KeyCode::P] = 'P';
	mapKeyCodes[KeyCode::Q] = 'Q';
	mapKeyCodes[KeyCode::R] = 'R';
	mapKeyCodes[KeyCode::S] = 'S';
	mapKeyCodes[KeyCode::T] = 'T';
	mapKeyCodes[KeyCode::U] = 'U';
	mapKeyCodes[KeyCode::V] = 'V';
	mapKeyCodes[KeyCode::W] = 'W';
	mapKeyCodes[KeyCode::X] = 'X';
	mapKeyCodes[KeyCode::Y] = 'Y';
	mapKeyCodes[KeyCode::Z] = 'Z';

	mapKeyCodes[KeyCode::Key_0] = '0';
	mapKeyCodes[KeyCode::Key_1] = '1';
	mapKeyCodes[KeyCode::Key_2] = '2';
	mapKeyCodes[KeyCode::Key_3] = '3';
	mapKeyCodes[KeyCode::Key_4] = '4';
	mapKeyCodes[KeyCode::Key_5] = '5';
	mapKeyCodes[KeyCode::Key_6] = '6';
	mapKeyCodes[KeyCode::Key_7] = '7';
	mapKeyCodes[KeyCode::Key_8] = '8';
	mapKeyCodes[KeyCode::Key_9] = '9';


	mapKeyCodes[KeyCode::LeftShift] = VK_LSHIFT;
	mapKeyCodes[KeyCode::RightShift] = VK_RSHIFT;
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