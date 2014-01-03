#ifndef __SHADER_TECHNIQUE__
#define __SHADER_TECHNIQUE__

#include "cg.h"

#include "cgD3D9.h"

#include "cgGL.h"

#include <vector>
#include <map>
#include <string>
#include "boost\algorithm\string.hpp"
#include "../core/math/Matrix4x4.h"
#include "../Material.h"
#include "../PlatformRenderer.h"

using namespace std;

class ShaderPass;

class ShaderTechnique
{

public:

	ShaderTechnique(CGtechnique technique);

	int GetPassCount();

	void BeginPass(int index);
	void EndPass(int index);

	CGtechnique technique;
	const char* name;

protected:

	vector<ShaderPass*> passes;
	typedef vector<ShaderPass*>::iterator PassIterator;

	int passCount;
};

#endif