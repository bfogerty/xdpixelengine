#include "ShaderTechnique.h"
#include "ShaderPass.h"
#include "RenderEngine.h"
#include "Material.h"

//-----------------------------------------------------------------------------------
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
		passes.push_back(shaderPass);
		cgPass = cgGetNextPass(cgPass);
	} while ( cgPass != 0 );
}

//-----------------------------------------------------------------------------------
void ShaderTechnique::BeginPass(int index)
{
	passes[index]->BeginPass();
}

//-----------------------------------------------------------------------------------
void ShaderTechnique::EndPass(int index)
{
	passes[index]->EndPass();
}

//-----------------------------------------------------------------------------------
int ShaderTechnique::GetPassCount()
{
	return passCount;
}

