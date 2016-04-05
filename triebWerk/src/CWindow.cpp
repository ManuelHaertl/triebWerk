#include <CWindow.h>
#include <Windows.h>
#include <iostream>

triebWerk::CWindow::CWindow() : 
	m_Height(0),
	m_Width(0),
	m_IsFullscreen(false),
	m_ShowCursor(true),
	m_WindowHandle(NULL)
{
}

triebWerk::CWindow::~CWindow()
{
}

bool triebWerk::CWindow::Initialize(const bool a_IsFullscreen, const unsigned short a_ScreenWidth, const unsigned short a_ScreenHeight, const char* a_WindowName)
{
	//Set initialize values
	m_Height = a_ScreenHeight;
	m_Width = a_ScreenWidth;
	m_IsFullscreen = a_IsFullscreen;

	//window sytle
	WNDCLASSEX mainWindowDescription;
	ZeroMemory(&mainWindowDescription, sizeof(WNDCLASSEX));
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

	//Create window 
	m_WindowHandle = CreateWindowEx(NULL,
		a_WindowName,
		a_WindowName,
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		0,
		0,
		windowRectangle.right - windowRectangle.left,
		windowRectangle.bottom - windowRectangle.top,
		NULL,
		NULL,
		GetModuleHandle(NULL),
		NULL);

	if (m_WindowHandle == NULL)
		return false;

	ShowWindow(m_WindowHandle, SW_SHOWDEFAULT);
	m_ShowCursor = true;

	//If fullscreen change normal window above to fullscreen
	if (a_IsFullscreen)
		ChangeWindowSettings(true, m_Width, m_Height);

	return true;
}

const MSG triebWerk::CWindow::GetWindowEvent()
{
	MSG msg = { 0 };

	if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);

		DispatchMessage(&msg);
	}

	return msg;
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

bool triebWerk::CWindow::IsWindowFullscreen()
{
	return m_IsFullscreen;
}

int triebWerk::CWindow::GetMaximalDisplayWidth()
{
	DEVMODE dmScreenSettings;
	EnumDisplaySettings(NULL, 0, &dmScreenSettings);
	return dmScreenSettings.dmPelsWidth;
}

int triebWerk::CWindow::GetMaximalDisplayHeight()
{
	DEVMODE dmScreenSettings;
	EnumDisplaySettings(NULL, 0, &dmScreenSettings);
	return dmScreenSettings.dmPelsHeight;
}

void triebWerk::CWindow::ChangeWindowSettings(const bool a_IsFullscreen, const unsigned short a_ScreenWidth, const unsigned short a_ScreenHeight)
{
	//Set new values
	m_IsFullscreen = a_IsFullscreen;
	m_Width = a_ScreenWidth;
	m_Height = a_ScreenHeight;

	//Set window rect
	RECT windowRectangle = { 0, 0, a_ScreenWidth ,a_ScreenHeight };

	DEVMODE dmScreenSettings;
	EnumDisplaySettings(NULL, 0, &dmScreenSettings);
	dmScreenSettings.dmSize = sizeof(dmScreenSettings);

	//If Fullscreen set target resolution if not set "normal" resolution
	if (a_IsFullscreen)
	{
		dmScreenSettings.dmPelsWidth = a_ScreenWidth;
		dmScreenSettings.dmPelsHeight = a_ScreenHeight;
	}
	else
	{
		dmScreenSettings.dmPelsWidth = static_cast<DWORD>(GetMaximalDisplayWidth());
		dmScreenSettings.dmPelsHeight = static_cast<DWORD>(GetMaximalDisplayHeight());
	}
	dmScreenSettings.dmBitsPerPel = 32;
	dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

	ChangeDisplaySettingsEx(NULL, &dmScreenSettings, NULL, CDS_FULLSCREEN, NULL);

	//Set the style for fullscreen or window
	if(a_IsFullscreen)
		SetWindowLongPtr(m_WindowHandle, GWL_STYLE, WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP);
	else
		SetWindowLongPtr(m_WindowHandle, GWL_STYLE, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX);

	//If window calculate correct client space
	if (!a_IsFullscreen)
		AdjustWindowRect(&windowRectangle, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, FALSE);

	//Resize the window and draw it new
	SetWindowPos(m_WindowHandle, NULL, 0, 0, windowRectangle.right - windowRectangle.left, windowRectangle.bottom - windowRectangle.top, SWP_FRAMECHANGED | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_SHOWWINDOW);

	//Disable Cursor if Fullscreen enable if window
	if (m_ShowCursor == true && a_IsFullscreen)
	{
		ShowCursor(false);
		m_ShowCursor = false;
	}
	else if(m_ShowCursor == false && !a_IsFullscreen)
	{
		ShowCursor(true);
		m_ShowCursor = true;
	}
}