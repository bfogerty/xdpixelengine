#include "Material.h"
#include "RenderEngine.h"
#include "PlatformRenderer.h"
#include "shaders/ShaderProgram.h"
#include "shaders/ShaderTechnique.h"
#include "./resource/texture2d/Texture2D.h"

//-----------------------------------------------------------------------------------
Material::Material( char* program )
{
	shader = new ShaderProgram("./assets/shaders/samplecgfx.fx");
	//shader = new ShaderProgram("./assets/shaders/quad.fx");
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



