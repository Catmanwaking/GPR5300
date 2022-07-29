#pragma once
#include <Windows.h>

LRESULT CALLBACK WndProc(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam);

class Window
{
public:
	INT Init(HINSTANCE hInstance, UINT width, UINT height);
	BOOL Run();
	void DeInit();

	HWND GetWindowHandle() { return hWnd; }

private:
	RECT wr = {};
	HWND hWnd;
};

