#ifndef		__RENDERER_CONFIG__
#define		__RENDERER_CONFIG__

struct RendererConfig
{
public:

	enum RENDER_API
	{
		DX9 = 0,
		OPENGL,
	};

	int ScreenWidth;
	int ScreenHeight;
	bool FullScreen;
	char *WindowHandle;
	RENDER_API RenderAPI;

	float GetAspectRatio()
	{
		return (float)(ScreenWidth)/ScreenHeight;
	}
};

#endif