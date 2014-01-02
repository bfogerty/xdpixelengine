#ifndef __SHADER_PROGRAM__
#define __SHADER_PROGRAM__

#include "platform.h"
#include "cg.h"

#ifdef COMPILE_DX9_RENDERER
#include "cgD3D9.h"
#endif

#ifdef COMPILE_OPENGL_RENDERER
#include "cgGL.h"
#endif

#include <vector>
#include <map>
#include "boost\algorithm\string.hpp"
#include "../core/math/Matrix4x4.h"
#include "../Material.h"
#include "../PlatformRenderer.h"
using namespace std;

class ShaderTechnique;

class ShaderProgram
{

public:

	ShaderProgram(char *program);

	void BindProgam(Matrix4x4 mapMVP, Material::RenderMethod renderMethod, PlatformRenderer* renderer, GameObject* gameObject);
	void UnBindProgam();


	char *program;
	CGcontext myCgContext;
	CGprofile myCgVertexProfile;
	CGprogram myCgVertexProgram;
	CGeffect myCgEffect;

	ShaderTechnique *selectedTechnique;
	map<const char*, ShaderTechnique*> techniques;


	typedef map<const char*, ShaderTechnique*>::iterator TechniqueIterator;

	// Hack
	CGparameter mvpParam;
};

#endif