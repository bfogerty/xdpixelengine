#include "platform.h"
#include "ShaderProgram.h"
#include "ShaderTechnique.h"
#include "RenderEngine.h"
#include "PlatformRenderer.h"
#include "config/EngineConfig.h"

struct IDirect3DDevice9;

ShaderProgram::ShaderProgram( char* program )
{
	this->program = program;

	selectedTechnique = 0;

#ifdef COMPILE_DX9_RENDERER
	if( EngineConfig::GetRendererAPI() == RendererConfig::DX9 )
	{
		IDirect3DDevice9 *pDev = (IDirect3DDevice9*) RenderEngine::GetInstance()->GetRenderer()->GetDeviceContext();
		cgD3D9SetDevice( (IDirect3DDevice9*) RenderEngine::GetInstance()->GetRenderer()->GetDeviceContext());
	}
#endif

	myCgContext = cgCreateContext();
	cgSetParameterSettingMode(myCgContext, CG_DEFERRED_PARAMETER_SETTING);

#ifdef COMPILE_DX9_RENDERER
	if( EngineConfig::GetRendererAPI() == RendererConfig::DX9 )
	{
		cgD3D9RegisterStates( myCgContext );
	}
#endif

#ifdef COMPILE_OPENGL_RENDERER
	if( EngineConfig::GetRendererAPI() == RendererConfig::OPENGL )
	{
		cgGLRegisterStates( myCgContext );
		cgGLSetManageTextureParameters( myCgContext, CG_TRUE );

		//CGprofile prof = cgGLGetLatestProfile( CG_GL_VERTEX );
	}
#endif

	myCgEffect = cgCreateEffectFromFile( myCgContext, program, 0 );
	CGerror e = cgGetError();
	const char* msg = cgGetLastErrorString(&e);


	CGtechnique technique = cgGetFirstTechnique(myCgEffect);
	do 
	{
		bool validTechnique = cgValidateTechnique( technique );
		e = cgGetError();
		msg = cgGetLastErrorString(&e);

		ShaderTechnique *shaderTechnique = new ShaderTechnique(technique);

		if( selectedTechnique == 0 && validTechnique )
		{
			selectedTechnique = shaderTechnique;
		}

		techniques[shaderTechnique->name] = shaderTechnique;
		technique = cgGetNextTechnique(technique);
	} while (technique != 0);
}

void ShaderProgram::BindProgam(Matrix4x4 mapMVP, Material::RenderMethod renderMethod, PlatformRenderer* renderer, GameObject* gameObject)
{
	CGparameter mvpParam = cgGetNamedEffectParameter(myCgEffect, "mvp");
	cgSetParameterValuefc(mvpParam, 16, mapMVP.mMatrix);

	selectedTechnique->BindProgam(mapMVP, renderMethod, renderer, gameObject);
}

void ShaderProgram::UnBindProgam()
{
	selectedTechnique->UnBindProgam();
	//cgD3D9UnbindProgram(myCgVertexProgram);
}