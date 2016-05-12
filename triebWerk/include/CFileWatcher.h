#pragma once
#include <string>
#include <vector>
#include <thread>
#include <Windows.h>
#include <stdlib.h>

namespace triebWerk
{
	class CFileWatcher
	{
	public:
		enum class EFileEventTypes
		{
			Added,
			Removed,
			Modified,
			Renamed
		};

		struct SFileEvent
		{
			EFileEventTypes Event;
			std::string FileName;
		};

	private:
		std::vector<SFileEvent> m_Events;
		std::thread m_Thread;
		bool m_Active = false;
		HANDLE m_FileHandle;


	public:
		void Watch(const char* a_pDirectory, bool a_WatchSubDirectory);
		void StopWatching();

	private:
		void Spectate(const char* a_pDirectory);
		void GetLastestEvents(std::vector<SFileEvent>* a_pOutEvents);

	public:
		CFileWatcher();
		~CFileWatcher();


	};
}