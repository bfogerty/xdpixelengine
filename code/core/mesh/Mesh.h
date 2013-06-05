#ifndef __MESH__
#define __MESH__
#include <vector>
#include "./math/Vector3.h"
#include "../renderer/Color.h"
using namespace std;

class TriangleData
{
public:
	Vector3 verts[3];
	Color colors[3];
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

	TriangleData *GetTriangleData(int iTriangle);
	void Build();

	vector<TriangleData*> triangleData;
};

#endif
