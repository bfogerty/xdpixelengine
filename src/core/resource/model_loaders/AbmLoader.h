#ifndef __ABM_LOADER__
#define __ABM_LOADER__

#include <fstream>
using namespace std;

class AbmData;
class AbmClipData;

class AbmLoader
{
public:
	static AbmData* Load(const char* filename);

	static void ReadInt(ifstream &f, int &outVal);
	static void ReadShort(ifstream &f, short &outVal);
	static void ReadFloat(ifstream &f, float &outVal);

protected:

	static void ParseClips( ifstream &f, AbmData *data );
	static void ParseFrames( ifstream &f, AbmData *data, AbmClipData &clip );
	static void ParseTextureCoordinate( ifstream &f, AbmData *data );
	static void ParseTriangles( ifstream &f, AbmData *data );
};

#endif