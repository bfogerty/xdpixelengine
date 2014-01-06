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
class Texture2D;

class ShaderProgram
{

public:

	ShaderProgram( const char *program );

	ShaderTechnique *GetTechnique();
	int GetPassCount();

	void SetFloat( const char* parameter, float val );
	void SetVector3( const char* parameter, Vector3 val );
	void SetVector4( const char* parameter, Vector4 val );
	void SetMatrix( const char* parameter, Matrix4x4 matrix );

	void SetTexture( const char* parameter, Texture2D *tex2D );

	const char *program;
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