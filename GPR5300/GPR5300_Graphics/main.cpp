#include "Window.h"
#include "D3D.h"
#include "Mesh.h"
#include "Camera.h"
#include "Scene.h"
#include "Vector3.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szCmd, int nCmdShow)
{
	int numArgs = 0;
	LPWSTR* args = CommandLineToArgvW(GetCommandLineW(), &numArgs);
	BOOL windowed = ((args[1] != nullptr) && (*args[1] == *L"-w")) ? true : false; //commandline windowed

	UINT width = windowed ? 1080 : GetSystemMetrics(SM_CXSCREEN);
	UINT height = windowed ? 720 : GetSystemMetrics(SM_CYSCREEN);

	Window window = {};	
	INT error = window.Init(hInstance, width, height, windowed);
	if (error) return error;

	D3D d3d = {};
	error = d3d.Init(window.GetWindowHandle(), width, height, windowed);
	if (error) return error;

	Scene scene = {};
	error = scene.Init(d3d.GetDevice(), d3d.GetDeviceContext(), d3d.GetDepthStencilView(), width, height);
	if (error) return error;

	while (window.Run())
	{
		scene.Update();

		d3d.BeginScene();

		scene.Render();

		d3d.EndScene();
	}

	scene.DeInit();
	d3d.DeInit();
	window.DeInit();

	return 0;
}
