#ifndef __PLATFORM__
#define __PLATFORM__

//-----------------------------------------------------------------------------------
// Hardware Platform
//-----------------------------------------------------------------------------------
#define WIN_RELEASE 1
//#define PS2_RELEASE 1

//-----------------------------------------------------------------------------------
// Renderer API
//-----------------------------------------------------------------------------------
#ifndef PS2_RELEASE
	//#define COMPILE_DX9_RENDERER			1
	#define COMPILE_OPENGL_RENDERER			1

	//#define USE_DX9_RENDERER				1
	#define USE_OPENGL_RENDERER				1
#endif

#endif