#include "core/mesh/Mesh.h"
#include "graphics/RenderEngine.h"

//-----------------------------------------------------------------------------------
Mesh::Mesh()
{
	m_pVertexBuffer = 0;
}

//-----------------------------------------------------------------------------------
Mesh::~Mesh()
{

}

//-----------------------------------------------------------------------------------
void Mesh::Build()
{
	if( triangleData.size() <= 0 )
	{
		triangleData.resize(triangles.size());
		for(vector<TriangleData*>::iterator it = triangleData.begin(); it != triangleData.end(); ++it )
		{
			*it = new TriangleData();
		}
	}

	int iTriangleIndicieCount = triangles.size();
	int triangleIndex = 0;
	for( int i=0; i < iTriangleIndicieCount; i += 3 )
	{
		TriangleData *pTri = triangleData[triangleIndex++];
		int vertIndicies[] = {
			triangles[i + 0]->VertexIndex,
			triangles[i + 1]->VertexIndex,
			triangles[i + 2]->VertexIndex
		};
		pTri->verts[0] = verticies[vertIndicies[0]];
		pTri->verts[1] = verticies[vertIndicies[1]];
		pTri->verts[2] = verticies[vertIndicies[2]];

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

			int normalIndicies[] = {
				triangles[i + 0]->NormalIndex,
				triangles[i + 1]->NormalIndex,
				triangles[i + 2]->NormalIndex
			};

			pTri->normals[0] = *normals[normalIndicies[0]];
			pTri->normals[1] = *normals[normalIndicies[1]];
			pTri->normals[2] = *normals[normalIndicies[2]];
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

		//triangleData.push_back(pTri);
	}

	if (m_pVertexBuffer == NULL)
	{
		m_pVertexBuffer = RenderEngine::GetInstance()->GetRenderer()->CreateVertexBuffer(triangleData.size());
	}

	if (m_pVertexBuffer != NULL)
	{
		RenderEngine::GetInstance()->GetRenderer()->UploadMeshToGPU(this);
	}
}

//-----------------------------------------------------------------------------------
TriangleData *Mesh::GetTriangleData(int iTriangleIndex)
{
	if( iTriangleIndex < 0 )
	{
		return 0;
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
	verticies.reserve(pSrcMesh->verticies.size());
	uvs.reserve(pSrcMesh->uvs.size());
	colors.reserve(pSrcMesh->colors.size());
	triangles.reserve(pSrcMesh->triangles.size());
	normals.reserve(pSrcMesh->normals.size());

	std::copy(pSrcMesh->verticies.begin(), pSrcMesh->verticies.end(), std::back_inserter(verticies));
	std::copy(pSrcMesh->uvs.begin(), pSrcMesh->uvs.end(), std::back_inserter(uvs));
	std::copy(pSrcMesh->colors.begin(), pSrcMesh->colors.end(), std::back_inserter(colors));
	std::copy(pSrcMesh->triangles.begin(), pSrcMesh->triangles.end(), std::back_inserter(triangles));
	std::copy(pSrcMesh->normals.begin(), pSrcMesh->normals.end(), std::back_inserter(normals));

	Build();
}