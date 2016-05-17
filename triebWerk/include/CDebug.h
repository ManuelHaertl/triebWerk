#pragma once
#include <CDebugCamera.h>
#include <CDebugLogfile.h>

namespace triebWerk
{
	class CDebug
	{
	public:
		CDebugCamera m_DebugCamera;

	private:
		bool m_DebugMode;

	public:
		CDebug();
		~CDebug();

	public:
		void Update();

        void Enable();
        void Disable();
        bool IsInDebug() const;
	};
}