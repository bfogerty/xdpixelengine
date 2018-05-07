#ifndef __SHADER_TECHNIQUE__
#define __SHADER_TECHNIQUE__

#include "external/cg/include/Cg/cg.h"
#include "external/cg/include/Cg/cgD3D9.h"
#include "external/cg/include/Cg/cgGL.h"
#include "core/math/Matrix4x4.h"
#include "renderer/Material.h"
#include "renderer/PlatformRenderer.h"
#include <vector>
#include <map>
#include <string>
#include "core/math/Matrix4x4.h"
#include "renderer/Material.h"
#include "renderer/PlatformRenderer.h"

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