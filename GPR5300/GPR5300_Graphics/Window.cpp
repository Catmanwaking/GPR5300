#include "Window.h"
#include <WinUser.h>
#include <stdio.h>
#include <memory>

INT Window::Init(HINSTANCE hInstance, UINT width, UINT height, BOOL windowed)
{
	DWORD style = WS_OVERLAPPEDWINDOW;
	UINT screenWidth = GetSystemMetrics(SM_CXSCREEN);
	UINT screenHeight = GetSystemMetrics(SM_CYSCREEN);
	POINT pos = { (screenWidth - width) >> 1, (screenHeight - height) >> 1 };
	RECT wr = { pos.x, pos.y, pos.x + width, pos.y + height };
	if(windowed) AdjustWindowRect(&wr, style, false);

	WNDCLASS wc = { };
	wc.hInstance = hInstance;
	wc.hbrBackground = CreateSolidBrush(RGB(0, 0, 0));
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wc.lpszClassName = TEXT("Direct3D 11");
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = WndProc;

	if (RegisterClass(&wc) == 0) return 10;

	hWnd = CreateWindow
	(
		wc.lpszClassName,
		wc.lpszClassName,
		style,
		wr.left, wr.top,
		wr.right - wr.left, wr.bottom - wr.top,
		nullptr,
		nullptr,
		hInstance,
		nullptr
	);

	if (hWnd == nullptr) return 12;

	ShowWindow(hWnd, SW_NORMAL);
	SetFocus(hWnd);

	return 0;
}

// Handles WindowMessages until WM_QUIT is sent.
BOOL Window::Run()
{
	static MSG msg = {};
	if (PeekMessage(&msg, nullptr, 0, UINT_MAX, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.message != WM_QUIT;
}

void Window::DeInit()
{
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CLOSE:
		DestroyWindow(hWnd);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE)
			DestroyWindow(hWnd);
		break;

	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	return 0;
}
