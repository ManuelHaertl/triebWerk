#include <Windows.h>
#include "..\include\CWindow.h"
#include <iostream>

triebWerk::CWindow::CWindow()
{
}

triebWerk::CWindow::~CWindow()
{
}

const bool triebWerk::CWindow::Initialize(const bool a_IsFullscreen, const unsigned short a_ScreenWidth, const unsigned short a_ScreenHeight, const char* a_WindowName)
{
	if (a_IsFullscreen)
	{
		WNDCLASSEX wc;
		DEVMODE dmScreenSettings;
		int posX, posY;
		HMODULE hModule;

		hModule = GetModuleHandle(NULL);

		wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
		wc.lpfnWndProc = WindowProcedure;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = hModule;
		wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
		wc.hIconSm = wc.hIcon;
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
		wc.lpszMenuName = NULL;
		wc.lpszClassName = a_WindowName;
		wc.cbSize = sizeof(WNDCLASSEX);

		RegisterClassEx(&wc);

		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = GetSystemMetrics(SM_CXSCREEN);
		dmScreenSettings.dmPelsHeight = GetSystemMetrics(SM_CYSCREEN);
		dmScreenSettings.dmBitsPerPel = 32;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		m_Width = dmScreenSettings.dmPelsWidth;
		m_Height = dmScreenSettings.dmPelsHeight;

		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);

		posX = posY = 0;

		m_WindowHandle = CreateWindowEx(WS_EX_APPWINDOW, a_WindowName, a_WindowName,
			WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP,
			posX, posY, a_ScreenWidth, a_ScreenHeight, NULL, NULL, hModule, NULL);

		ShowWindow(m_WindowHandle, SW_SHOW);
		SetForegroundWindow(m_WindowHandle);
		SetFocus(m_WindowHandle);

		ShowCursor(false);
	}
	else
	{
		WNDCLASSEX mainWindowDescription;

		memset(&mainWindowDescription, 0, sizeof(WNDCLASSEX));
		mainWindowDescription.cbSize = sizeof(WNDCLASSEX);
		mainWindowDescription.style = CS_HREDRAW | CS_VREDRAW;
		mainWindowDescription.lpfnWndProc = WindowProcedure;
		mainWindowDescription.hInstance = GetModuleHandle(NULL);
		mainWindowDescription.hCursor = LoadCursor(NULL, IDC_ARROW);
		mainWindowDescription.hbrBackground = (HBRUSH)COLOR_WINDOW;
		mainWindowDescription.lpszClassName = a_WindowName;

		RegisterClassEx(&mainWindowDescription);

		RECT windowRectangle = { 0, 0, a_ScreenWidth ,a_ScreenHeight };
		AdjustWindowRect(&windowRectangle, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, FALSE);

		m_Width = a_ScreenWidth;
		m_Height = a_ScreenHeight;

		m_WindowHandle = CreateWindowEx(NULL,
			a_WindowName,
			a_WindowName,
			WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
			100,
			100,
			windowRectangle.right - windowRectangle.left,
			windowRectangle.bottom - windowRectangle.top,
			NULL,
			NULL,
			GetModuleHandle(NULL),
			NULL);


		if (m_WindowHandle == NULL)
			return false;

		ShowWindow(m_WindowHandle, SW_SHOWDEFAULT);
	}

	return true;
}

const MSG triebWerk::CWindow::GetWindowEvent()
{
	MSG msg = { 0 };

	if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);

		DispatchMessage(&msg);
		return msg;
	}
}

LRESULT triebWerk::CWindow::WindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	} break;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

HWND* triebWerk::CWindow::GetModulHanle()
{
	return &m_WindowHandle;
}

const unsigned short triebWerk::CWindow::GetScreenWidth()
{
	return m_Width;
}

const unsigned short triebWerk::CWindow::GetScreenHeight()
{
	return m_Height;
}
