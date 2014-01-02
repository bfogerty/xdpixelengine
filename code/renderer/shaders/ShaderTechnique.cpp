#include "ShaderTechnique.h"
#include "ShaderPass.h"
#include "RenderEngine.h"
#include "Material.h"

struct IDirect3DDevice9;

ShaderTechnique::ShaderTechnique( CGtechnique technique )
{
	this->technique = technique;
	this->name = cgGetTechniqueName(this->technique);

	passCount = 0;

	CGpass cgPass = cgGetFirstPass(this->technique);
	do 
	{
		if( cgPass == 0 )
		{
			break;
		}

		++passCount;
		ShaderPass *shaderPass = new ShaderPass( cgPass ); 
		passes[shaderPass->name] = shaderPass;
		cgPass = cgGetNextPass(cgPass);
	} while ( cgPass != 0 );
}

void ShaderTechnique::BindProgam(Matrix4x4 mapMVP, Material::RenderMethod renderMethod, PlatformRenderer* renderer, GameObject* gameObject)
{
	bool validated = cgValidateTechnique( technique );
	CGerror e = cgGetError();
	const char* msg = cgGetLastErrorString(&e);

	for( PassIterator it = passes.begin(); it != passes.end(); ++it)
	{
		ShaderPass *pass = (ShaderPass *)it->second;
		pass->BeginPass();
	}

	renderMethod( renderer, gameObject );
}

void ShaderTechnique::UnBindProgam()
{
	for( PassIterator it = passes.begin(); it != passes.end(); ++it)
	{
		ShaderPass *pass = (ShaderPass *)it->second;
		pass->EndPass();
	}	
}

int ShaderTechnique::GetPassCount()
{
	return passCount;
}