#include "platform.h"
#include "ShaderProgram.h"
#include "ShaderTechnique.h"
#include "RenderEngine.h"
#include "PlatformRenderer.h"
#include "config/EngineConfig.h"
#include "./resource/texture2d/Texture2D.h"

#ifdef COMPILE_DX9_RENDERER
#include "./resource/texture2d/DX9Texture2D.h"
#endif

#ifdef COMPILE_OPENGL_RENDERER
#include "./resource/texture2d/OpenGLTexture2D.h"
#endif


//-----------------------------------------------------------------------------------
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

//-----------------------------------------------------------------------------------
/*
void ShaderProgram::BindProgam(Matrix4x4 mapMVP, Material::RenderMethod renderMethod, PlatformRenderer* renderer, GameObject* gameObject)
{
	CGparameter mvpParam = cgGetNamedEffectParameter(myCgEffect, "mvp");
	cgSetParameterValuefc(mvpParam, 16, mapMVP.mMatrix);

	selectedTechnique->BindProgam(mapMVP, renderMethod, renderer, gameObject);
}
*/

//-----------------------------------------------------------------------------------
ShaderTechnique *ShaderProgram::GetTechnique()
{
	return selectedTechnique;
}

//-----------------------------------------------------------------------------------
int ShaderProgram::GetPassCount()
{
	if( selectedTechnique == 0 )
	{
		return 0;
	}

	return selectedTechnique->GetPassCount();
}

//-----------------------------------------------------------------------------------
void ShaderProgram::SetFloat( const char* parameter, float val )
{
	CGparameter param = cgGetNamedEffectParameter(myCgEffect, parameter);
	cgSetParameterValuefc(param, 1, &val);
}

//-----------------------------------------------------------------------------------
void ShaderProgram::SetVector3( const char* parameter, Vector3 val )
{
	float vals[3];
	vals[0] = val.x();
	vals[1] = val.y();
	vals[2] = val.z();

	CGparameter param = cgGetNamedEffectParameter(myCgEffect, parameter);
	cgSetParameterValuefc(param, 3, vals);
}

//-----------------------------------------------------------------------------------
void ShaderProgram::SetVector4( const char* parameter, Vector4 val )
{
	float vals[4];
	vals[0] = val.x();
	vals[1] = val.y();
	vals[2] = val.z();
	vals[3] = val.w();

	CGparameter param = cgGetNamedEffectParameter(myCgEffect, parameter);
	cgSetParameterValuefc(param, 4, vals);
}

//-----------------------------------------------------------------------------------
void ShaderProgram::SetMatrix( const char* parameter, Matrix4x4 matrix )
{
	CGparameter param = cgGetNamedEffectParameter(myCgEffect, parameter);
	cgSetParameterValuefc(param, 16, matrix.mMatrix);
}

//-----------------------------------------------------------------------------------
void ShaderProgram::SetTexture( const char* parameter, Texture2D *tex2D )
{
	if( tex2D == 0 )
	{
		return;
	}

#ifdef COMPILE_DX9_RENDERER
	if( EngineConfig::GetRendererAPI() == RendererConfig::DX9 )
	{
		DX9Texture2D *dx9Tex2D = (DX9Texture2D *)tex2D;
		CGparameter param = cgGetNamedEffectParameter(myCgEffect, parameter);
		cgD3D9SetTextureParameter(param, dx9Tex2D->mpTexture);
	}
#endif

#ifdef COMPILE_OPENGL_RENDERER
	if( EngineConfig::GetRendererAPI() == RendererConfig::OPENGL )
	{
		OpenGLTexture2D *glTex2D = (OpenGLTexture2D*)tex2D;
		CGparameter param = cgGetNamedEffectParameter(myCgEffect, parameter);
		cgGLSetTextureParameter(param, glTex2D->iTextureID);
	}
#endif

}




