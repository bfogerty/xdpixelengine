#include "platform.h"
#include "Engine.h"
#include <iostream>
using namespace std;

#ifdef WIN_RELEASE
#include <windows.h>

HWND gHWND;
HINSTANCE gHINSTANCE;

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
		break;

	case WM_QUIT:
		return 0;
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hOrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	EngineConfig::LoadConfigFile();

	gHINSTANCE = hInstance;

	WNDCLASS wc;
	ZeroMemory(&wc, sizeof(WNDCLASS));

	wc.style = CS_HREDRAW|CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.hInstance = gHINSTANCE;
	wc.hIcon = ::LoadIcon(0, IDI_APPLICATION);
	wc.hCursor = ::LoadCursor(0, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)::GetStockObject(NULL_BRUSH);
	wc.lpszClassName = "Windows3DClass";

	RegisterClass(&wc);

	RECT rcClientArea;
	rcClientArea.left = 0;
	rcClientArea.right = static_cast<LONG>(EngineConfig::renderConfig.ScreenWidth);
	rcClientArea.top = 0;
	rcClientArea.bottom = static_cast<LONG>(EngineConfig::renderConfig.ScreenHeight);

	AdjustWindowRect(&rcClientArea, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU, false);

	gHWND = CreateWindow(wc.lpszClassName, "xdpixel", WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
		0,0,rcClientArea.right - rcClientArea.left, rcClientArea.bottom - rcClientArea.top
		,NULL,NULL,gHINSTANCE,NULL);

	if(gHWND == NULL)
	{
		::MessageBox(NULL,"Error creating window.", "Windows Error", MB_OK|MB_ICONERROR);
		return false;
	}

	ShowWindow(gHWND, nShowCmd);
	UpdateWindow(gHWND);

	EngineConfig::WindowHandle = (char*)(gHWND);
	Engine *pEngine = new Engine();

	int iLastTime = timeGetTime();
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));
	GetMessage(&msg,0,0,0);
	while(msg.message != WM_QUIT)
	{
		if(PeekMessage(&msg, 0, 0, 0, PM_REMOVE) != 0)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			int iCurrentTime = timeGetTime();
			float fElapsedTime = static_cast<float>((iCurrentTime - iLastTime));
			
			pEngine->Update();

			if( GetKeyState(VK_ESCAPE) & 0x8000 )
			{
				PostQuitMessage(0);
			}

			iLastTime = iCurrentTime;
		}

	}

	delete pEngine;
	pEngine = NULL;

	return (int)msg.wParam;
}
#elif PS2_RELEASE

int main( int argc, char *argv[] )
{
	EngineConfig engineConfig;
	engineConfig.WindowHandle = NULL;
	Engine *pEngine = new Engine(engineConfig);
	while( 1 == 1 )
	{
		pEngine->Update();
	}

	delete pEngine;
	pEngine = NULL;

	return 0;
}

#endif