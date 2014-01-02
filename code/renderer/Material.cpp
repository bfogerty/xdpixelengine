#include "Material.h"
#include "RenderEngine.h"
#include "PlatformRenderer.h"
#include "shaders/ShaderProgram.h"

Material::Material( char* program )
{
	shader = new ShaderProgram("./assets/shaders/samplecgfx.fx");
	//shader = new ShaderProgram("./assets/shaders/quad.fx");
}

void Material::SetMVPMatrix( Matrix4x4 matMVP )
{
	this->matMVP = matMVP;
}

void Material::BindProgam(RenderMethod renderMethod, PlatformRenderer* renderer, GameObject* gameObject)
{
	shader->BindProgam(matMVP, renderMethod, renderer, gameObject);
}

void Material::UnBindProgam()
{
	shader->UnBindProgam();
}