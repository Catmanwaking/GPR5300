#include "Window.h"
#include "D3D.h"
#include "Mesh.h"
#include "Camera.h"

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

	Mesh mesh = {};
	error = mesh.Init(d3d.GetDevice());
	if (error != 0)
		return error;

	Camera camera = {};
	error = camera.Init(d3d.GetDevice(), width, height);
	if (error != 0)
		return error;

	while (window.Run())
	{
		camera.Update();
		mesh.Update();

		d3d.BeginScene();

		mesh.Render(d3d.GetDevice());

		d3d.EndScene();
	}

	camera.DeInit();
	mesh.DeInit();
	d3d.DeInit();
	window.DeInit();

	return 0;
}
