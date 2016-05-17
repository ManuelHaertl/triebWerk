#pragma once

#include <Windows.h>
#include <stdio.h>
#include <string>

#define DebugLogfile CDebugLogfile::Instance()

#define MAX_BUFFER 1024
#define L_FAIL false
#define L_OK true

namespace triebWerk
{
	class CDebugLogfile
	{
	public:
		enum class EColor
		{
			Black,
			Red,
			Green,
			Blue,
			Yellow
		};

	private:
		FILE* m_pFile;
		bool m_ErrorOccurred;

	public:
		static CDebugLogfile& Instance();

	private:
		CDebugLogfile();
		~CDebugLogfile();

	public:
		void CreateLogfile(const char* a_LogfileName);
		void WriteTopic(const char*  a_Topic, unsigned int a_Size);
		void LogText(const char* a_Text);
		void LogText(EColor a_Color, bool a_List, const char* a_Text);
		void LogText(EColor a_Color, const char* a_Text);
		void LogfText(const char* a_Text, ...);
		void LogfText(EColor a_Color, const char* a_Text, ...);
		void LogfText(EColor a_Color, bool a_List, const char* a_Text, ...);
		void FunctionResult(const char* a_pFunctionName, bool a_Result);
	};
}
