#ifndef __MATERIAL__
#define __MATERIAL__

#include "cg.h"
#include "cgD3D9.h"
#include "../core/math/Matrix4x4.h"
#include "../core/math/Vector3.h"
#include "../core/math/Vector4.h"
#include <vector>
#include <string>
#include "boost\algorithm\string.hpp"
using namespace std;

class ShaderProgram;
class PlatformRenderer;
class GameObject;
class Texture2D;

class Material
{

public:

	typedef void (*RenderMethod)(PlatformRenderer*,GameObject*);

	Material(char *program);

	int GetPassCount();
	void BeginPass(int index);
	void EndPass(int index);

	void SetFloat( const char* parameter, float val );
	void SetVector3( const char* parameter, Vector3 val );
	void SetVector4( const char* parameter, Vector4 val );
	void SetMatrix( const char* parameter, Matrix4x4 val );

	void SetTexture( const char* parameter, Texture2D *tex2D );

protected:
	ShaderProgram *shader;
};

#endif