#pragma once
#include <Windows.h>
#include <queue>

namespace triebWerk
{
	class CWindow
	{
	public:
		struct SWindowConfiguration
		{
			bool m_Fullscreen;
			unsigned m_ScreenWidth;
			unsigned m_ScreenHeight;
			const char* m_WindowName;
		};

	private:
		static const DWORD WindowStyleFullscreen = WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP;
		static const DWORD WindowStyleWindowed = WS_OVERLAPPEDWINDOW;

		HWND m_WindowHandle;
		std::queue<MSG> m_MessageQueue;

		unsigned short m_Width;
		unsigned short m_Height;

		unsigned short m_DefaultWidth;
		unsigned short m_DefaultHeight;

		bool m_IsFullscreen;
		bool m_ShowCursor;
		bool m_IsSizing;

	public:
		CWindow();
		~CWindow();

	public:
		bool Initialize(const SWindowConfiguration& a_rWindowConfig);

		const MSG GetWindowEvent();

		LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

		void ChangeWindowSettings(const bool a_IsFullscreen, const unsigned short a_ScreenWidth, const unsigned short a_ScreenHeight);
		
		HWND& GetWindowHandle();

		static LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

		inline unsigned short GetScreenWidth() const;
		inline unsigned short GetScreenHeight() const;
		
		bool IsWindowFullscreen();
		void UpdateWindow();

		static int GetMaximalDisplayWidth();
		static int GetMaximalDisplayHeight();
	};
}