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
	for( int i=0; i < iTriangleIndicieCount; i += 3 )
	{
		TriangleData *pTri = new TriangleData();
		pTri->verts[0] = *verticies[triangles[i + 0]->VertexIndex];
		pTri->verts[1] = *verticies[triangles[i + 1]->VertexIndex];
		pTri->verts[2] = *verticies[triangles[i + 2]->VertexIndex];

		if( colors.size() > 0 )
		{
			pTri->colors[0] = *colors[ triangles[i+0]->ColorIndex ];
			pTri->colors[1] = *colors[ triangles[i+1]->ColorIndex ];
			pTri->colors[2] = *colors[ triangles[i+2]->ColorIndex ];
		}
		else
		{
			pTri->colors[0] = Color(Color::WHITE);
			pTri->colors[1] = Color(Color::WHITE);
			pTri->colors[2] = Color(Color::WHITE);
		}

		if(uvs.size() > 0 )
		{
			pTri->uvs[0] = *uvs[triangles[i + 0]->UVIndex];
			pTri->uvs[1] = *uvs[triangles[i + 1]->UVIndex];
			pTri->uvs[2] = *uvs[triangles[i + 2]->UVIndex];
		}

		if( normals.size() > 0)
		{
			pTri->normals[0] = *normals[triangles[i + 0]->NormalIndex];
			pTri->normals[1] = *normals[triangles[i + 1]->NormalIndex];
			pTri->normals[2] = *normals[triangles[i + 2]->NormalIndex];
		}
		else
		{
			//Calculate Normals
			Vector3 vec0To1 = pTri->verts[1] - pTri->verts[0];
			Vector3 vec0To2 = pTri->verts[2] - pTri->verts[0];

			vec0To1.Normalize();
			vec0To2.Normalize();
			Vector3 vecNormal = Vector3::Cross(vec0To1, vec0To2);
			vecNormal.Normalize();

			pTri->normals[0] = vecNormal;
			pTri->normals[1] = vecNormal;
			pTri->normals[2] = vecNormal;
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

//-----------------------------------------------------------------------------------
void Mesh::Clone(Mesh *pSrcMesh)
{
	verticies.clear();
	uvs.clear();
	colors.clear();
	triangles.clear();
	normals.clear();
	triangleData.clear();

	for(int i = 0; i<pSrcMesh->verticies.size(); ++i)
	{
		verticies.push_back(pSrcMesh->verticies[i]);
	}

	for(int i = 0; i<pSrcMesh->uvs.size(); ++i)
	{
		uvs.push_back(pSrcMesh->uvs[i]);
	}

	for(int i = 0; i<pSrcMesh->colors.size(); ++i)
	{
		colors.push_back(pSrcMesh->colors[i]);
	}

	for(int i = 0; i<pSrcMesh->triangles.size(); ++i)
	{
		triangles.push_back(pSrcMesh->triangles[i]);
	}

	for(int i = 0; i<pSrcMesh->normals.size(); ++i)
	{
		normals.push_back(pSrcMesh->normals[i]);
	}

	Build();
}