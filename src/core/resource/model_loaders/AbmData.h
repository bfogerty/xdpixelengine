#ifndef __ABM_DATA__
#define __ABM_DATA__

#include "../../math/Vector3.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class AbmTriangle
{
public:
	short VertexIndicies[3];
	short TextureCoordinateIndicies[3];

	Vector3 Normal;
};

class AbmTextureCoordinates
{
public:
	Vector3 UV;
};

class AbmFrameData
{
public:

	vector<Vector3> Verticies;
	vector<Vector3> Normals;
};

class AbmClipData
{
public:
	char ClipName[24];
	int FrameCount;
	int FramesPerSecond;

	vector<AbmFrameData> Frames;

	AbmClipData()
	{
		memset(ClipName, 0, 24);
	}

};

class AbmData
{
public:
	
	char FileId[4];
	int ExportVersion;
	int NumberOfTriangles;
	int NumberOfVerticies;
	int NumberOfTextureCoordinates;
	int NumberOfFrames;
	int SizeOfEachFrameInBytes;
	int NumberOfClips;
	vector<string> ClipNames;

	int OffsetToFrames;
	int OffsetToTextures;
	int OffsetToTriangles;

	vector<AbmClipData> Clips;
	vector<AbmTextureCoordinates> TextureCoordinates;
	vector<AbmTriangle> Triangles;

	AbmData();
};

#endif