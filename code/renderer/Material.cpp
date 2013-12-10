#include "Material.h"
#include "RenderEngine.h"
#include "PlatformRenderer.h"

struct IDirect3DDevice9;

Material::Material( char* program )
{
	this->program = program;

	IDirect3DDevice9 *pDev = (IDirect3DDevice9*) RenderEngine::GetInstance()->GetRenderer()->GetDeviceContext();
	cgD3D9SetDevice( (IDirect3DDevice9*) RenderEngine::GetInstance()->GetRenderer()->GetDeviceContext());

	myCgContext = cgCreateContext();
	cgSetParameterSettingMode(myCgContext, CG_DEFERRED_PARAMETER_SETTING);

	const char **profileOpts;

	/* Determine the best profile once a device to be set. */
	myCgVertexProfile = cgD3D9GetLatestVertexProfile();

	profileOpts = cgD3D9GetOptimalOptions(myCgVertexProfile);


	
	//myCgVertexProgram =
	//	cgCreateProgramFromFile(
	//	myCgContext,              /* Cg runtime context */
	//	CG_SOURCE,                /* Program in human-readable form */
	//	program,  /* Name of file containing program */
	//	myCgVertexProfile,        /* Profile: OpenGL ARB vertex program */
	//	"main",      /* Entry function name */
	//	profileOpts);             /* Pass optimal compiler options */

	myCgEffect = cgCreateEffectFromFile( myCgContext, program, 0 );

	
	CGtechnique technique = cgGetNamedTechnique( myCgEffect, "t0" );
	CGpass pass = cgGetFirstPass( technique );
	while( pass != 0 )
	{

		pass = cgGetNextPass( pass );
	}
	


	const char *strSpec = cgGetLastListing(myCgContext);
	const char *strError = cgGetErrorString(cgGetError());
	std::cout << cgGetErrorString(cgGetError());

	/*
	myCgVertexProgram = cgCreateProgramFromEffect( myCgEffect,
		myCgVertexProfile,
		const char * entry,
		const char ** args );
		*/
	cgD3D9LoadProgram(myCgVertexProgram, false, 0);
	const char *strSpec1 = cgGetLastListing(myCgContext);
	const char *strError1 = cgGetErrorString(cgGetError());
}

void Material::BindProgam()
{
	cgD3D9BindProgram(myCgVertexProgram);
}

void Material::UnBindProgam()
{
	cgD3D9UnbindProgram(myCgVertexProgram);
}