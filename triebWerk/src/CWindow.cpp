#include <CWindow.h>
#include <Windows.h>
#include <iostream>

triebWerk::CWindow::CWindow() : 
	m_Height(0),
	m_Width(0),
	m_IsFullscreen(false),
	m_ShowCursor(true),
	m_IsSizing(false)
{
}

triebWerk::CWindow::~CWindow()
{
	//If screen resolution is not user default, change it to user default before 
	if (m_DefaultHeight != GetSystemMetrics(SM_CYSCREEN) || m_DefaultWidth != GetSystemMetrics(SM_CXSCREEN))
	{
		DEVMODE dmScreenSettings = { 0 };
		EnumDisplaySettings(NULL, 0, &dmScreenSettings);
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = static_cast<DWORD>(m_DefaultWidth);
		dmScreenSettings.dmPelsHeight = static_cast<DWORD>(m_DefaultHeight);
		dmScreenSettings.dmBitsPerPel = 32;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		ChangeDisplaySettingsEx(NULL, &dmScreenSettings, NULL, CDS_FULLSCREEN, NULL);
	}
}

bool triebWerk::CWindow::Initialize(const CWindow::SWindowConfiguration& a_rConfiguration)
{
	//Get the default user screen resolution
	m_DefaultWidth = static_cast<unsigned short>(GetSystemMetrics(SM_CXSCREEN));
	m_DefaultHeight = static_cast<unsigned short>(GetSystemMetrics(SM_CYSCREEN));

	//Set initialize values
	m_Height = static_cast<unsigned short>(a_rConfiguration.m_ScreenWidth);
	m_Width = static_cast<unsigned short>(a_rConfiguration.m_ScreenHeight);
	m_IsFullscreen = a_rConfiguration.m_Fullscreen;

	//window sytle
	WNDCLASSEX mainWindowDescription;
	ZeroMemory(&mainWindowDescription, sizeof(WNDCLASSEX));
	mainWindowDescription.cbSize = sizeof(WNDCLASSEX);
	mainWindowDescription.style = CS_HREDRAW | CS_VREDRAW;
	mainWindowDescription.lpfnWndProc = WindowProcedure;
	mainWindowDescription.hInstance = GetModuleHandle(NULL);
	mainWindowDescription.hCursor = LoadCursor(NULL, IDC_ARROW);
	mainWindowDescription.hbrBackground = (HBRUSH)COLOR_WINDOW;
	mainWindowDescription.lpszClassName = a_rConfiguration.m_WindowName;

	RegisterClassEx(&mainWindowDescription);

	RECT windowRectangle = { 0, 0, static_cast<long>(a_rConfiguration.m_ScreenWidth), static_cast<long>(a_rConfiguration.m_ScreenHeight) };
	AdjustWindowRect(&windowRectangle, WindowStyleWindowed, FALSE);

	//Create window 
	m_WindowHandle = CreateWindowEx(NULL,
		a_rConfiguration.m_WindowName,
		a_rConfiguration.m_WindowName,
		WindowStyleWindowed,
		0,
		0,
		windowRectangle.right - windowRectangle.left,
		windowRectangle.bottom - windowRectangle.top,
		NULL,
		NULL,
		GetModuleHandle(NULL),
		this);

	if (m_WindowHandle == NULL)
		return false;

	ShowWindow(m_WindowHandle, SW_SHOWDEFAULT);
	m_ShowCursor = true;

	//If fullscreen change normal "default" window above to fullscreen
	if (a_rConfiguration.m_Fullscreen)
		ChangeWindowSettings(true, m_Width, m_Height);

	return true;
}

const MSG triebWerk::CWindow::GetWindowEvent()
{
	MSG msg = { 0 };
	if (m_MessageQueue.size() != 0)
	{
		msg = m_MessageQueue.front();
		m_MessageQueue.pop();
	}

	return msg;
}

LRESULT triebWerk::CWindow::WindowProcedure(HWND a_HWnd, UINT a_Message, WPARAM a_WParam, LPARAM a_LParam)
{
		CWindow *pThis = nullptr;

		if (a_Message == WM_NCCREATE)
		{
			CREATESTRUCT* pCreate = reinterpret_cast<CREATESTRUCT*>(a_LParam);
			pThis = reinterpret_cast<CWindow*>(pCreate->lpCreateParams);
			SetWindowLongPtr(a_HWnd, GWLP_USERDATA, (LONG_PTR)pThis);
	
			pThis->m_WindowHandle = a_HWnd;
		}
		else
		{
			pThis = reinterpret_cast<CWindow*>(GetWindowLongPtr(a_HWnd, GWLP_USERDATA));
		}
		if (pThis)
		{
			return pThis->HandleMessage(a_Message, a_WParam, a_LParam);
		}
		else
		{
			return DefWindowProc(a_HWnd, a_Message, a_WParam, a_LParam);
		}
}

LRESULT triebWerk::CWindow::HandleMessage(UINT a_Message, WPARAM wParam, LPARAM lParam)
{
	switch (a_Message)
	{
	case WM_SIZE:
	{
		MSG msg = { 0 };
		msg.message = a_Message;
		msg.lParam = lParam;
		msg.wParam = wParam;
		m_MessageQueue.push(msg);

		if (wParam == SIZE_MAXIMIZED)
		{
			MSG msgMax = { 0 };
			msgMax.message = WM_EXITSIZEMOVE;
			msgMax.lParam = lParam;
			msgMax.wParam = wParam;
			m_MessageQueue.push(msg);
		}
	}break;
	
	case WM_SIZING:
	{
		m_IsSizing = true;
	}break;

	case WM_EXITSIZEMOVE:
	{
		if (m_IsSizing)
		{
			MSG msg = { 0 };
			msg.message = a_Message;
			msg.lParam = lParam;
			msg.wParam = wParam;
			m_MessageQueue.push(msg);

			m_IsSizing = false;
		}

	}break;
	
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	}break;

	default:
		return DefWindowProc(m_WindowHandle, a_Message, wParam, lParam);
	}

	return true;
}

HWND& triebWerk::CWindow::GetWindowHandle()
{
	return m_WindowHandle;
}

inline unsigned short triebWerk::CWindow::GetScreenWidth() const
{
	return m_Width;
}

inline unsigned short triebWerk::CWindow::GetScreenHeight() const
{
	return m_Height;
}

bool triebWerk::CWindow::IsWindowFullscreen()
{
	return m_IsFullscreen;
}

void triebWerk::CWindow::UpdateWindow()
{
	MSG msg = { 0 };

	if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		m_MessageQueue.push(msg);

		DispatchMessage(&msg);
	}
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
		dmScreenSettings.dmPelsWidth = static_cast<DWORD>(m_DefaultWidth);
		dmScreenSettings.dmPelsHeight = static_cast<DWORD>(m_DefaultHeight);
	}
	dmScreenSettings.dmBitsPerPel = 32;
	dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

	long error = ChangeDisplaySettingsEx(NULL, &dmScreenSettings, NULL, CDS_FULLSCREEN, NULL);
	if (error != DISP_CHANGE_SUCCESSFUL)
	{
		//Make error
	}

	//Set the style for fullscreen or window
	if(a_IsFullscreen)
		SetWindowLongPtr(m_WindowHandle, GWL_STYLE, WindowStyleFullscreen);
	else
		SetWindowLongPtr(m_WindowHandle, GWL_STYLE, WindowStyleWindowed);

	//If window calculate correct client space
	if (!a_IsFullscreen)
		AdjustWindowRect(&windowRectangle, WindowStyleWindowed, FALSE);

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