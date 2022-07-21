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

	//Camera camera = {};
	//error = camera.Init(d3d.GetDevice(), width, height);
	//if (error != 0)
	//	return error;

	Time time = {};
	error = time.Init();
	if (error != 0)
		return error;

	Material material{};
	error = material.Init(d3d.GetDevice(), TEXT("rock.jpg"));
	if (error != 0)
		return error;

	//D3DLIGHT9 lightData = {};
	//lightData.Type = D3DLIGHT_POINT;
	//lightData.Position = { 0.0f, 0.0f, -0.5f };
	//lightData.Ambient = { 0.2f, 0.2f, 0.2f, 1.0f };
	//lightData.Diffuse = { 1.0f, 1.0f, 1.0f, 1.0f };
	//lightData.Specular = { 1.0f, 1.0f, 1.0f, 1.0f };
	//lightData.Range = 10.0f;
	//lightData.Attenuation0 = 1.0f;
	//lightData.Attenuation1 = 0.2f;
	//lightData.Attenuation2 = 0.1f;

	//Light light = {};
	//error = light.Init(lightData, 0);
	//if (error != 0)
	//	return error;

	while (window.Run())
	{
		time.Update();
		//camera.Update();
		mesh.Update();

		d3d.BeginScene();

		//light.Render(d3d.GetDevice());
		material.Render(d3d.GetDeviceContext());
		mesh.Render(d3d.GetDeviceContext());

		d3d.EndScene();
	}

	//light.DeInit();
	material.DeInit();
	time.DeInit();
	//camera.DeInit();
	mesh.DeInit();
	d3d.DeInit();
	window.DeInit();

	return 0;
}
