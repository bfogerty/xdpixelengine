#ifndef __SHADER_PASS__
#define __SHADER_PASS__

#include "cg.h"
#include "cgD3D9.h"
#include <vector>
#include "boost\algorithm\string.hpp"
#include "../core/math/Matrix4x4.h"
using namespace std;

class ShaderPass
{

public:

	ShaderPass(CGpass pass);

	void BeginPass();
	void EndPass();

	CGpass pass;
	const char* name;
};

#endif