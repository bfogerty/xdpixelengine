#include "ShaderPass.h"
#include "RenderEngine.h"
#include "PlatformRenderer.h"

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