#ifndef __BASE_OBJECT__
#define __BASE_OBJECT__
#include "string"
using namespace std;

class BaseObject
{

public:
	BaseObject();
	virtual ~BaseObject();

	virtual string ToString() { return ""; }
};

#endif