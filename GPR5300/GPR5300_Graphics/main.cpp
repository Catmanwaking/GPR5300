#include "Window.h"
#include "D3D.h"
#include "Mesh.h"
#include "Camera.h"
#include "Scene.h"
#include "Vector3.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szCmd, int nCmdShow)
{
	UINT width = 1080;
	UINT height = 720;
	BOOL windowed = false;

	Window window = {};	
	INT error = window.Init(hInstance, width, height);
	if (error != 0) return error;

	D3D d3d = {};
	error = d3d.Init(window.GetWindowHandle(), width, height, windowed);
	if (error != 0) return error;

	if (!windowed)
	{
		width = d3d.GetWidth();
		height = d3d.GetHeight();

	}

	Scene scene = {};
	error = scene.Init(d3d.GetDevice(), width, height);
	if (error != 0) return error;

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
