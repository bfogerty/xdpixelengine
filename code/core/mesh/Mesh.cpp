#include "Mesh.h"

//-----------------------------------------------------------------------------------
Mesh::Mesh()
{
	
}

//-----------------------------------------------------------------------------------
Mesh::~Mesh()
{

}

//-----------------------------------------------------------------------------------
void Mesh::Build()
{
	int iTriangleIndicieCount = triangles.size();
	for( int i=0; i< iTriangleIndicieCount; i += 3 )
	{
		TriangleData *pTri = new TriangleData();
		pTri->verts[0] = *verticies[triangles[i + 0]];
		pTri->verts[1] = *verticies[triangles[i + 1]];
		pTri->verts[2] = *verticies[triangles[i + 2]];

		pTri->colors[0] = *colors[i+0];
		pTri->colors[1] = *colors[i+1];
		pTri->colors[2] = *colors[i+2];

		if(uvs.size() > 0 )
		{
			pTri->uvs[0] = *uvs[i+0];
			pTri->uvs[1] = *uvs[i+1];
			pTri->uvs[2] = *uvs[i+2];
		}

		triangleData.push_back(pTri);
	}
}

//-----------------------------------------------------------------------------------
TriangleData *Mesh::GetTriangleData(int iTriangleIndex)
{
	if( iTriangleIndex < 0 )
	{
		return NULL;
	}

	return triangleData[iTriangleIndex];
}