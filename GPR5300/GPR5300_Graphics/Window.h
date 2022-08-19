#pragma once
#include <Windows.h>

LRESULT CALLBACK WndProc(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam);

class Window
{
public:
	//Creates and shows the Window
	INT Init(HINSTANCE hInstance, UINT width, UINT height, BOOL windowed);
	//Handles windowmessages
	BOOL Run();
	void DeInit();

	HWND GetWindowHandle() { return hWnd; }

private:
	RECT wr = {};
	HWND hWnd;
};

