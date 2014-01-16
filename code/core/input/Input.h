#ifndef __INPUT__
#define __INPUT__
#include "../core/platform.h"
#include "../core/math/Vector3.h"
#include "Keycode.h"
#include <map>

#ifdef WIN_RELEASE
#include "windows.h"
#endif

class Input
{

public:
	static Input *mInst;
	static Input* Inst();
	void Initialize();

	bool GeyKey(int key);
	bool GetMouseButton( int key );

	Vector3 FromClientToScreenSpace( Vector3 position );
	Vector3 FromScreenSpaceToClientSpace( Vector3 position );

	Vector3 GetWindowPositionInScreenSpace();

	Vector3 GetMousePosition();
	void SetMousePosition( Vector3 position );

	void ShowMouseCursor( bool show );

private:
	
	std::map<int, int> mapKeyCodes;
	std::map<int, int> mapMouseKeyCodes;

#ifdef WIN_RELEASE
	POINT mousePosition;
#endif

};

#endif