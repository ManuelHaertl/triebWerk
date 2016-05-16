#include <CFileWatcher.h>

void triebWerk::CFileWatcher::Watch(const char * a_pDirectory, bool a_WatchSubDirectory)
{
	if (m_Active)
	{
		StopWatching();
	}

	m_Active = true;
	m_PathWatching = a_pDirectory;

	m_Thread = std::thread(&CFileWatcher::Spectate,this, a_pDirectory);
}

void triebWerk::CFileWatcher::StopWatching()
{
	m_Events.clear();
	m_Active = false;
	if (m_FileHandle != INVALID_HANDLE_VALUE)
	{
		//Stop the ReadDirectoryChangesW so the thread can be joined
		CancelIoEx(m_FileHandle, NULL);

		m_Thread.join();
	}
}


void triebWerk::CFileWatcher::GetLastestEvents(std::vector<SFileEvent>* a_pOutEvents)
{
	for (size_t i = 0; i < m_Events.size(); i++)
	{
		a_pOutEvents->push_back(m_Events[i]);
	}

	m_Events.clear();
}

triebWerk::CFileWatcher::CFileWatcher() :
	m_Active(false),
	m_FileHandle(INVALID_HANDLE_VALUE)
{
}

triebWerk::CFileWatcher::~CFileWatcher()
{
}

void triebWerk::CFileWatcher::Spectate(const char * a_pDirectory)
{
	FILE_NOTIFY_INFORMATION buffer[1024] = { 0 };

	DWORD returnSize = 0;

	m_FileHandle = CreateFile(a_pDirectory, FILE_LIST_DIRECTORY, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, NULL, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, NULL);

	while (m_Active)
	{
		SFileEvent fileEvent;

		bool result = ReadDirectoryChangesW(m_FileHandle, (LPVOID)&buffer, sizeof(buffer), TRUE, FILE_NOTIFY_CHANGE_CREATION | FILE_NOTIFY_CHANGE_LAST_WRITE | FILE_NOTIFY_CHANGE_FILE_NAME, &returnSize, 0, 0);

		switch (buffer[0].Action)
		{
		case FILE_ACTION_ADDED:
			fileEvent.Event = EFileEventTypes::Added;
			break;
		case FILE_ACTION_REMOVED:
			fileEvent.Event = EFileEventTypes::Removed;
			break;
		case FILE_ACTION_MODIFIED:
			fileEvent.Event = EFileEventTypes::Modified;
			break;
		case FILE_ACTION_RENAMED_OLD_NAME:
			fileEvent.Event = EFileEventTypes::Renamed;
			break;
		}
		char charBuffer[100];
		size_t* pSizeOfChars = nullptr;
		wcstombs_s(pSizeOfChars, charBuffer, buffer[0].FileName, 100);

		fileEvent.FileName = charBuffer;

		m_Events.push_back(fileEvent);
	}
}
