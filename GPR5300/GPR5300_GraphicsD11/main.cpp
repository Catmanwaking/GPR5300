#include "Window.h"
#include "D3D.h"
#include "Mesh.h"
#include "Camera.h"
#include "Time.h"
#include "Material.h"
#include "Light.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szCmd, int nCmdShow)
{
	SetProcessDPIAware();

	UINT width = 1080;
	UINT height = 720;
	BOOL windowed = true;

	Window window = {};	
	INT error = window.Init(hInstance, width, height);
	if (error != 0) return error;

	D3D d3d = {};
	error = d3d.Init(window.GetWindowHandle(), width, height, windowed);
	if (error != 0) return error;

	Mesh mesh = {};
	error = mesh.Init(d3d.GetDevice());
	if (error != 0) return error;

	Camera camera = {};
	error = camera.Init(width, height);
	if (error != 0)
		return error;

	Time time = {};
	error = time.Init();
	if (error != 0)
		return error;

	Material material{};
	error = material.Init(d3d.GetDevice(), TEXT("rock.jpg"));
	if (error != 0)
		return error;

	Light::LightData lightData = {};
	lightData.direction = { 1.0f, -1.0f, 1.0f };
	lightData.color = { 1.0f, 1.0f, 1.0f, 1.0f };
	lightData.intensity = 1.0f;

	Light light = {};
	error = light.Init(d3d.GetDevice(), lightData, 0);
	if (error != 0)
		return error;

	while (window.Run())
	{
		time.Update();
		camera.Update();
		mesh.Update();

		d3d.BeginScene();

		light.Render(d3d.GetDeviceContext());
		material.Render(d3d.GetDeviceContext(), mesh.GetWorldMatrix(), camera.GetViewMatrix(), camera.GetProjectionMatrix());
		mesh.Render(d3d.GetDeviceContext());

		//2nd Mesh depth stenicling

		d3d.EndScene();
	}

	light.DeInit();
	material.DeInit();
	time.DeInit();
	camera.DeInit();
	mesh.DeInit();
	d3d.DeInit();
	window.DeInit();

	return 0;
}
