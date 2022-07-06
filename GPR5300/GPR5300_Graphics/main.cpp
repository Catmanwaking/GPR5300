#include "Window.h"
#include "D3D.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szCmd, int nCmdShow)
{
	UINT width = 1080;
	UINT height = 720;
	BOOL windowed = true;

	Window window = {};	
	INT error = window.Init(hInstance, width, height);
	if (error != 0)
		return error;

	D3D d3d = {};
	error = d3d.Init(window.GetWindowHandle(), width, height, windowed);
	if (error != 0)
		return error;

	while (window.Run())
	{
		d3d.BeginScene();

		//draw calls

		d3d.EndScene();
	}

	d3d.DeInit();
	window.DeInit();

	return 0;
}
