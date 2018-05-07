#ifndef __SHADER_PASS__
#define __SHADER_PASS__

#include "external/cg/include/Cg/cg.h"
#include "external/cg/include/Cg/cgD3D9.h"
#include "core/math/Matrix4x4.h"
//#include "boost/algorithm/string.hpp"
#include <string>
#include <vector>

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