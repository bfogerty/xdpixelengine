#ifndef __INPUT__
#define __INPUT__
#include "../core/platform.h"
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

private:
	
	std::map<int, int> mapKeyCodes;

};

#endif