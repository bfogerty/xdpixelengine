#ifndef		__RENDERER_CONFIG__
#define		__RENDERER_CONFIG__

struct RendererConfig
{
public:
	int ScreenWidth;
	int ScreenHeight;
	bool FullScreen;
	char *WindowHandle;

	float GetAspectRatio()
	{
		return (float)(ScreenWidth)/ScreenHeight;
	}
};

#endif