#ifndef __SHADER_TECHNIQUE__
#define __SHADER_TECHNIQUE__

#include "cg.h"

#include "cgD3D9.h"

#include "cgGL.h"

#include <vector>
#include <map>
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

	void BindProgam(Matrix4x4 mapMVP, Material::RenderMethod renderMethod, PlatformRenderer* renderer, GameObject* gameObject);
	void UnBindProgam();

	int GetPassCount();

	CGtechnique technique;
	const char* name;

protected:

	map<const char*, ShaderPass*> passes;
	typedef map<const char*, ShaderPass*>::iterator PassIterator;

	int passCount;
};

#endif