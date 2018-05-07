#include "renderer/shaders/ShaderPass.h"
#include "renderer/RenderEngine.h"
#include "renderer/PlatformRenderer.h"

ShaderPass::ShaderPass( CGpass pass )
{
	this->pass = pass;
	this->name = cgGetPassName( this->pass );
}

void ShaderPass::BeginPass()
{
	cgSetPassState( this->pass );

	CGerror e = cgGetError();
	const char* msg = cgGetLastErrorString(&e);
}

void ShaderPass::EndPass()
{
	cgResetPassState( this->pass );
}