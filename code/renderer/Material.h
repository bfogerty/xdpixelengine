#ifndef __MATERIAL__
#define __MATERIAL__

#include "cg.h"
#include "cgD3D9.h"
#include "../core/math/Matrix4x4.h"
#include "../core/math/Vector3.h"
#include "../core/math/Vector4.h"
#include <vector>
#include "boost\algorithm\string.hpp"
using namespace std;

class ShaderProgram;
class PlatformRenderer;
class GameObject;

class Material
{

public:

	typedef void (*RenderMethod)(PlatformRenderer*,GameObject*);

	Material(char *program);

	void BindProgam(RenderMethod renderMethod, PlatformRenderer* renderer, GameObject* gameObject);
	void UnBindProgam();

	ShaderProgram *shader;

	// HACK
	void SetMVPMatrix( Matrix4x4 matMVP );

	Matrix4x4 matMVP;

};

#endif