#ifndef __MATERIAL__
#define __MATERIAL__

#include "external/cg/include/CG/cg.h"
#include "external/cg/include/CG/cgD3D9.h"
#include "core/math/Matrix4x4.h"
#include "core/math/Vector3.h"
#include "core/math/Vector4.h"
#include <vector>
#include <map>
#include <string>

using namespace std;

class ShaderProgram;
class PlatformRenderer;
class GameObject;
class Texture2D;

class Material
{
public:

	Material( std::string name );
	Material( std::string name, const char *shaderProgramFilePath );

	void SetShaderProgram( const char *shaderProgramFilePath );
	int GetPassCount();
	void BeginPass(int index);
	void EndPass(int index);

	void SetInt( const char* parameter, int val );
	void SetFloat( const char* parameter, float val );
	void SetVector3( const char* parameter, Vector3 val );
	void SetVector4( const char* parameter, Vector4 val );
	void SetMatrix( const char* parameter, Matrix4x4 val );
	void SetString( const char* parameter, const char* val );

	void SetTexture( const char* parameter, Texture2D *tex2D );

	void AddTextureEntry( std::string name, Texture2D *tex2D );
	Texture2D* GetTextureEntry( std::string name );
	Texture2D* GetMainTextureEntry();

	void ApplyTextures();

protected:
	ShaderProgram *shader;
	std::string name;

	typedef map<std::string, Texture2D *>::iterator TextureIterator;
	map<std::string, Texture2D *> textures;
	Texture2D *mainTexture;
};

#endif