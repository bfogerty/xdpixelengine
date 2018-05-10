#ifndef __DEBUG_GFX__
#define __DEBUG_GFX__

#include "core/math/Matrix4x4.h"
#include "core/math/Vector3.h"
#include "core/math/Vector4.h"
#include "graphics/Color.h"
#include <vector>
#include <map>
#include <string>
using namespace std;

class PlatformRenderer;
class GameObject;

class DebugGfxLine
{
public:
	Vector3 start;
	Vector3 end;
	Color color;

	DebugGfxLine(Vector3 start, Vector3 end, Color color )
	{
		this->start = start;
		this->end = end;
		this->color = color;
	}
};

class DebugGfx
{
public:

	static void Initialize(GameObject *rootObject);
	static void Reset();
	static void Render(PlatformRenderer *platformRenderer);

	static void DrawLine(Vector3 start, Vector3 end, Color color);

protected:
	static vector<DebugGfxLine> lineList;
	static GameObject *rootObject;
};

#endif