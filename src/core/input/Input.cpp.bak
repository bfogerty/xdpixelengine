#include "Input.h"
#include "../config/EngineConfig.h"

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

	mapMouseKeyCodes[MouseKeyCode::Left] = VK_LBUTTON;
	mapMouseKeyCodes[MouseKeyCode::Middle] = VK_MBUTTON;
	mapMouseKeyCodes[MouseKeyCode::Right] = VK_RBUTTON;
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

bool Input::GetMouseButton( int key )
{

#ifdef WIN_RELEASE
	//return GetAsyncKeyState(mapMouseKeyCodes[key]) & 0x8000 != 0 ? TRUE : FALSE;
	return (GetKeyState(mapMouseKeyCodes[key]) & 0x100) != 0;
#endif

	return FALSE;
}

Vector3 Input::FromClientToScreenSpace( Vector3 position )
{
#ifdef WIN_RELEASE
	HWND hWnd = (HWND)EngineConfig::WindowHandle;
	POINT pnt;
	pnt.x = position.x();
	pnt.y = position.y();
	ClientToScreen(hWnd, &pnt);
	position.x( pnt.x );
	position.y( pnt.y );
	position.z( 0.00f );
#endif

	return position;
}

Vector3 Input::FromScreenSpaceToClientSpace( Vector3 position )
{
#ifdef WIN_RELEASE
	HWND hWnd = (HWND)EngineConfig::WindowHandle;
	POINT pnt;
	pnt.x = position.x();
	pnt.y = position.y();
	ScreenToClient(hWnd, &pnt);
	position.x( pnt.x );
	position.y( pnt.y );
	position.z( 0.00f );
#endif

	return position;
}

Vector3 Input::GetMousePosition()
{
	Vector3 pos;

#ifdef WIN_RELEASE
	HWND hWnd = (HWND)EngineConfig::WindowHandle;
	POINT mousePosition;
	GetCursorPos(&mousePosition);
	pos.x( mousePosition.x );
	pos.y( mousePosition.y );
	pos.z( 0.00f );
#endif

	return pos;
}

void Input::SetMousePosition( Vector3 position )
{
#ifdef WIN_RELEASE
	HWND hWnd = (HWND)EngineConfig::WindowHandle;
	POINT pnt;
	pnt.x = position.x();
	pnt.y = position.y();
	SetCursorPos(pnt.x, pnt.y);
#endif
}

Vector3 Input::GetWindowPositionInScreenSpace()
{
	Vector3 pos;

#ifdef WIN_RELEASE
	HWND hWnd = (HWND)EngineConfig::WindowHandle;
	RECT r;
	GetWindowRect(hWnd, &r);
	pos.x( r.left );
	pos.y( r.top );
	pos.z( 0.00f );
#endif

	return pos;
}

void Input::ShowMouseCursor( bool show )
{
#ifdef WIN_RELEASE

	if( !show )
	{
		while( ShowCursor( FALSE ) > 0 );
	}
	else
	{
		while( ShowCursor( TRUE ) < 0 );
	}

	//ShowCursor( show );
#endif
}