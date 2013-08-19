#include "ObjLoader.h"
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

Mesh *ObjLoader::Load(const char* strFileName)
{
	Mesh *pMesh = new Mesh();
	
	std::string buffer;
	ifstream f(strFileName);

	std::string pref_v = "v";
	std::string pref_n = "nv";
	std::string pref_f = "f";

	while( !f.eof() )
	{
		getline(f, buffer );

		if( buffer.substr(0,pref_v.size()) == pref_v)
		{
			// Parse vertex
			float vert[] = {0,0,0};
			sscanf(buffer.c_str(), "v %f %f %f", &vert[0], &vert[1], &vert[2]);
			pMesh->verticies.push_back(new Vector3( vert[0], vert[1], vert[2]));
		}
		else if( buffer.substr(0, pref_n.size()) == pref_n )
		{
			float normal[] = {0,0,0};
			sscanf(buffer.c_str(), "nv %f %f %f", &normal[0], &normal[1], &normal[2]);
			//pMesh->normals.push_back(new Vector3(normal[0], normal[1], normal[2]));
		}
		else if( buffer.substr(0, pref_f.size()) == pref_f)
		{
			int v[] = {0,0,0};
			int n[] = {0,0,0};
			sscanf(buffer.c_str(), "f %d//%d %d//%d %d//%d", &v[0], &n[0],&v[1], &n[1],&v[2], &n[2]);

			pMesh->triangles.push_back(v[0]-1);
			pMesh->triangles.push_back(v[1]-1);
			pMesh->triangles.push_back(v[2]-1);
		}
	}

	f.close();
	

	return pMesh;
}