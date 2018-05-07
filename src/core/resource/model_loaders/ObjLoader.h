#ifndef __OBJ_LOADER__
#define __OBJ_LOADER__

#include "../../mesh/Mesh.h"

class ObjLoader
{
public:
	static Mesh* Load(const char* strFilename);
};

#endif