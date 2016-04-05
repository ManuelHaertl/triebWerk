#pragma once
#include <Windows.h>

namespace triebWerk
{
	class CWindow
	{
	public:
		CWindow();
		~CWindow();
	public:
		bool Initialize(const bool a_IsFullscreen, const unsigned short a_ScreenWidth, const unsigned short a_ScreenHeight, const char* a_WindowName);
		
		const MSG GetWindowEvent();

		static LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

		void ChangeWindowSettings(const bool a_IsFullscreen, const unsigned short a_ScreenWidth, const unsigned short a_ScreenHeight);
		
		HWND* GetModulHanle();

		const unsigned short GetScreenWidth();
		const unsigned short GetScreenHeight();
		
		bool IsWindowFullscreen();

		static int GetMaximalDisplayWidth();
		static int GetMaximalDisplayHeight();

	private:
		HWND m_WindowHandle;

		unsigned short m_Width;
		unsigned short m_Height;

		bool m_IsFullscreen;
		bool m_ShowCursor;
	};
}