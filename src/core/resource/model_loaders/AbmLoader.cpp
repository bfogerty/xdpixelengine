#include "AbmLoader.h"
#include "AbmData.h"
#include <string>
#include <iostream>
using namespace std;

AbmData *AbmLoader::Load(const char* fileName)
{
	AbmData *data = new AbmData();

	ifstream abmFile( fileName, ios::in | ios::binary);

	abmFile.read(data->FileId,4);
	ReadInt(abmFile, data->ExportVersion);
	ReadInt(abmFile, data->NumberOfTriangles);
	ReadInt(abmFile, data->NumberOfVerticies);
	ReadInt(abmFile, data->NumberOfTextureCoordinates);
	ReadInt(abmFile, data->NumberOfFrames);
	ReadInt(abmFile, data->SizeOfEachFrameInBytes);
	ReadInt(abmFile, data->NumberOfClips);

	for(int i=0; i< data->NumberOfClips; ++i )
	{
		char buffer[24];
		abmFile.read(buffer, 24);
		data->ClipNames.push_back(buffer);
	}

	ReadInt(abmFile, data->OffsetToFrames);
	ReadInt(abmFile, data->OffsetToTextures);
	ReadInt(abmFile, data->OffsetToTriangles);

	ParseClips( abmFile, data );
	ParseTextureCoordinate( abmFile, data );
	ParseTriangles( abmFile, data );

	abmFile.close();

	return data;
}

void AbmLoader::ParseTriangles( ifstream &f, AbmData *data )
{
	f.seekg( data->OffsetToTriangles, ios_base::beg);
	data->Triangles.resize(data->NumberOfTriangles);
	int counter = 0;
	for( vector<AbmTriangle>::iterator it = data->Triangles.begin(); it != data->Triangles.end(); ++it )
	{
		AbmTriangle triangle;
		short x=0;
		short y=0;
		short z=0;

		AbmLoader::ReadShort( f, x );
		AbmLoader::ReadShort( f, y );
		AbmLoader::ReadShort( f, z );

		triangle.VertexIndicies[0] = x;
		triangle.VertexIndicies[1] = y;
		triangle.VertexIndicies[2] = z;

		short u=0;
		short v=0;
		short w=0;

		AbmLoader::ReadShort( f, u );
		AbmLoader::ReadShort( f, v );
		AbmLoader::ReadShort( f, w );

		triangle.TextureCoordinateIndicies[0] = u;
		triangle.TextureCoordinateIndicies[1] = v;
		triangle.TextureCoordinateIndicies[2] = w;

		float nx, ny, nz;
		AbmLoader::ReadFloat(f, nx);
		AbmLoader::ReadFloat(f, ny);
		AbmLoader::ReadFloat(f, nz);

		triangle.Normal = Vector3(nx,ny,nz);

		*it = triangle;
	}
}

void AbmLoader::ParseTextureCoordinate( ifstream &f, AbmData *data )
{
	f.seekg( data->OffsetToTextures, ios_base::beg);
	data->TextureCoordinates.resize(data->NumberOfTextureCoordinates);
	for( vector<AbmTextureCoordinates>::iterator it = data->TextureCoordinates.begin(); it != data->TextureCoordinates.end(); ++it )
	{
		float u,v;
		AbmTextureCoordinates textureCoordinateData;
		AbmLoader::ReadFloat( f, u );
		AbmLoader::ReadFloat( f, v );

		textureCoordinateData.UV.x(u);
		textureCoordinateData.UV.y(v);
		textureCoordinateData.UV.z(0.00f);

		*it = textureCoordinateData;
	}
}

void AbmLoader::ParseClips( ifstream &f, AbmData *data )
{
	f.seekg( data->OffsetToFrames, ios_base::beg);
	data->Clips.resize(data->NumberOfClips);
	for( vector<AbmClipData>::iterator vit = data->Clips.begin(); vit != data->Clips.end(); ++vit )
	{
		AbmClipData clipData;
		f.read(clipData.ClipName, 24);
		AbmLoader::ReadInt( f, clipData.FrameCount );
		AbmLoader::ReadInt(f, clipData.FramesPerSecond);
		
		ParseFrames( f, data, clipData );
		*vit = clipData;
	}
}

void AbmLoader::ParseFrames( ifstream &f, AbmData *data, AbmClipData &clip )
{
	clip.Frames.resize(clip.FrameCount);
	for(vector<AbmFrameData>::iterator fit = clip.Frames.begin(); fit != clip.Frames.end(); ++fit )
	{
		fit->Verticies.resize(data->NumberOfVerticies);
		fit->Normals.resize(data->NumberOfVerticies);
		
		for(int i=0; i < data->NumberOfVerticies; ++i)
		{
			float x,y,z;
			AbmLoader::ReadFloat( f, x );
			AbmLoader::ReadFloat( f, y );
			AbmLoader::ReadFloat( f, z );

			vector<Vector3>::iterator vit = fit->Verticies.begin()+i;
			*vit = Vector3(z,y,x);

			float nx,ny,nz;
			AbmLoader::ReadFloat( f, nx );
			AbmLoader::ReadFloat( f, ny );
			AbmLoader::ReadFloat( f, nz );

			vector<Vector3>::iterator nit = fit->Normals.begin()+i;
			*nit = Vector3(nz,ny,nx);
		}
	}
}

void AbmLoader::ReadInt(ifstream &f, int &outVal)
{
	f.read((char*)&outVal, 4);
}

void AbmLoader::ReadShort(ifstream &f, short &outVal)
{
	f.read((char*)&outVal, 2);

	if(outVal == 430 )
	{
		int a = 1;
		++a;
	}
}

void AbmLoader::ReadFloat(ifstream &f, float &outVal)
{
	f.read((char*)&outVal, 4);
}