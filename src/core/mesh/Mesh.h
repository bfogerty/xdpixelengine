#ifndef __MESH__
#define __MESH__
#include <vector>
#include "core/math/Vector3.h"
#include "graphics/Color.h"
#include "core/resource/texture2d/Texture2D.h"
using namespace std;

class TriangleData
{
public:
	Vector3 verts[3];
	Color colors[3];
	Vector3 uvs[3];
	Vector3 normals[3];
};

class Face
{
public:
	int VertexIndex;
	int NormalIndex;
	int UVIndex;
	int ColorIndex;

	Face( int vertexIndex, int normalIndex, int colorIndex)
	{
		VertexIndex = vertexIndex;
		NormalIndex = normalIndex;
		ColorIndex = colorIndex;
		UVIndex = -1;
	}

	Face( int vertexIndex, int normalIndex, int colorIndex, int uvIndex )
	{
		VertexIndex = vertexIndex;
		NormalIndex = normalIndex;
		ColorIndex = colorIndex;
		UVIndex = uvIndex;
	}
};

class Mesh
{

protected:
	void *m_pVertexBuffer;

public:
	Mesh();
	~Mesh();

	vector<Vector3> verticies;
	vector<Face*> triangles;
	vector<Vector3*> normals;
	vector<Color*> colors;
	vector<Vector3*> uvs;

	TriangleData *GetTriangleData(int iTriangle);
	void* GetVertexBuffer() { return m_pVertexBuffer; }
	void Build();

	void Clone(Mesh *pSrcMesh);

	vector<TriangleData*> triangleData;
};

#endif
