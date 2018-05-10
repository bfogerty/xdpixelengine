#include "graphics/Material.h"
#include "graphics/RenderEngine.h"
#include "graphics/PlatformRenderer.h"
#include "graphics/shaders/ShaderProgram.h"
#include "graphics/shaders/ShaderTechnique.h"
#include "core/resource/texture2d/Texture2D.h"

//-----------------------------------------------------------------------------------
Material::Material( std::string name )
{
	this->name = name;
	mainTexture = 0;
}

//-----------------------------------------------------------------------------------
Material::Material( std::string name, const char* shaderProgramFilePath )
{
	this->name = name;
	mainTexture = 0;

	SetShaderProgram( shaderProgramFilePath );
}

//-----------------------------------------------------------------------------------
void Material::SetShaderProgram( const char *shaderProgramFilePath )
{
	shader = new ShaderProgram( shaderProgramFilePath );
}

//-----------------------------------------------------------------------------------
int Material::GetPassCount()
{
	return shader->GetPassCount();
}

//-----------------------------------------------------------------------------------
void Material::BeginPass(int index)
{
	shader->selectedTechnique->BeginPass(index);
}

//-----------------------------------------------------------------------------------
void Material::EndPass(int index)
{
	shader->selectedTechnique->EndPass(index);
}

//-----------------------------------------------------------------------------------
void Material::SetInt( const char* parameter, int val )
{
	shader->SetInt(parameter, val);
}

//-----------------------------------------------------------------------------------
void Material::SetFloat( const char* parameter, float val )
{
	shader->SetFloat(parameter, val);
}

//-----------------------------------------------------------------------------------
void Material::SetVector3( const char* parameter, Vector3 val )
{
	shader->SetVector3( parameter, val );
}

//-----------------------------------------------------------------------------------
void Material::SetVector4( const char* parameter, Vector4 val )
{
	shader->SetVector4( parameter, val );
}

//-----------------------------------------------------------------------------------
void Material::SetMatrix( const char* parameter, Matrix4x4 val )
{
	shader->SetMatrix(parameter, val);
}

//-----------------------------------------------------------------------------------
void Material::SetTexture( const char* parameter, Texture2D *tex2D )
{
	shader->SetTexture( parameter, tex2D );
}

//-----------------------------------------------------------------------------------
void Material::SetString( const char* parameter, const char* val )
{
	shader->SetString( parameter, val );
}

//-----------------------------------------------------------------------------------
void Material::AddTextureEntry( std::string name, Texture2D *tex2D )
{
	if( textures.empty() )
	{
		mainTexture = tex2D;
	}

	textures[name] = tex2D;
}

//-----------------------------------------------------------------------------------
Texture2D* Material::GetMainTextureEntry()
{
	return mainTexture;
}

//-----------------------------------------------------------------------------------
Texture2D* Material::GetTextureEntry( std::string name )
{
	return textures[name];
}

//-----------------------------------------------------------------------------------
void Material::ApplyTextures()
{
	if( textures.empty() )
	{
		return;
	}

	for( TextureIterator it = textures.begin(); it != textures.end(); ++it )
	{
		SetTexture(it->first.c_str(), it->second);
	}
}
