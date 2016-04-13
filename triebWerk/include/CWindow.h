#pragma once
#include <Windows.h>
#include <queue>

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

		LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

		void ChangeWindowSettings(const bool a_IsFullscreen, const unsigned short a_ScreenWidth, const unsigned short a_ScreenHeight);
		
		HWND* GetWindowHandle();

		const unsigned short GetScreenWidth();
		const unsigned short GetScreenHeight();
		
		bool IsWindowFullscreen();
		void UpdateWindow();

		static int GetMaximalDisplayWidth();
		static int GetMaximalDisplayHeight();

	private:
		HWND m_WindowHandle;
		std::queue<MSG> m_MessageQueue;

		unsigned short m_Width;
		unsigned short m_Height;

		unsigned short m_DefaultWidth;
		unsigned short m_DefaultHeight;

		bool m_IsFullscreen;
		bool m_ShowCursor;
		bool m_IsSizing;
	};
}