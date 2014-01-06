#ifndef __MATERIAL_LOADER__
#define __MATERIAL_LOADER__

#include <map>

class Material;

class MaterialLoader
{
public:
	static Material* Load(const char* strFilename);


protected:
	static const char* ReadFileIntoString( const char* fileName );
	static void SetShaderParam( Material* mat, std::map<std::string, std::string> mapParams);
};

#endif