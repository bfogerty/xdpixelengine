#ifndef __MESH__
#define __MESH__
#include <vector>
#include "./math/Vector3.h"
#include "../renderer/Color.h"
#include "../resource/texture2d/Texture2D.h"
using namespace std;

class TriangleData
{
public:
	Vector3 verts[3];
	Color colors[3];
	Vector3 uvs[3];
};

class Mesh
{

public:
	Mesh();
	~Mesh();

	vector<Vector3*> verticies;
	vector<int> triangles;
	vector<Vector3*> normals;
	vector<Color*> colors;
	vector<Vector3*> uvs;

	TriangleData *GetTriangleData(int iTriangle);
	void Build();

	vector<TriangleData*> triangleData;
};

#endif
