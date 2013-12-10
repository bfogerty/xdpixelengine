#ifndef __MATERIAL__
#define __MATERIAL__

#include "cg.h"
#include "cgD3D9.h"
#include <vector>
using namespace std;

class Material
{

public:

	Material(char *program);

	void BindProgam();
	void UnBindProgam();


	char *program;
	CGcontext myCgContext;
	CGprofile myCgVertexProfile;
	CGprogram myCgVertexProgram;
	CGeffect myCgEffect;

};

#endif