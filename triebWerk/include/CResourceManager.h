#pragma once
#include <string>
#include <vector>
#include <Windows.h>
#include <unordered_map>

#include <EFileType.h>
#include <CTilesetMap.h>
#include <CTMXParser.h>
#include <CStringHasher.h>
#include <CINIParser.h>
#include <loadPNG\lodepng.h>

namespace triebWerk
{
	class CResourceManager
	{
	private:
		struct SFile
		{
			std::string FilePath;
			std::string FileName;
			EFileType FileType;
		};
	private:
		//Tilesets
		typedef std::unordered_map<size_t, CTilesetMap*> CTilesetHashMap;
		typedef std::pair<size_t, CTilesetMap*> CTilesetPair;

		//Config INI
		typedef std::unordered_map<size_t, CConfiguration*> CConfigurationMap;
		typedef std::pair<size_t, CConfiguration*> CConfigurationPair;

	private:
		CTilesetHashMap m_TilesetBuffer;
		CConfigurationMap m_ConfigurationBuffer;

		std::string m_ModulPath;

	public:
		CResourceManager();
		~CResourceManager();

	public:
		bool Initialize();
		void CleanUp();
		
		const char& GetModulPath();

		//Load Interface User
		void LoadAllFilesInFolder(const char* a_pPath);
		void LoadAllSpecificFilesInFolder(EFileType a_FileType, const char* a_pPath);
		void LoadSpecificFile(const char* a_pPath);

		//Get Interface
		CTilesetMap* GetTileset(const char* a_pTilesetName);
		CConfiguration* GetConfiguration(const char* a_pConfigurationName);

		//Unload
		void UnloadTileset(const char* a_pTilesetName);
		void UnloadConfiguration(const char* a_pConfigurationName);

	private:
		//Load actual data
		void LoadFile(SFile a_File);
		void LoadPNG(SFile a_File);
		void LoadOBJ(SFile a_File);
		void LoadMP3(SFile a_File);
		void LoadTMX(SFile a_File);
		void LoadHLSL(SFile a_File);
		void LoadINI(SFile a_File);

		bool SetModulPath();
		std::vector<SFile> SearchFolderForAllFiles(const char* a_FolderToLoad);

		//String helper functions
		bool CompareFileTypes(std::string a_Name, const char* a_ExpectedType);
		std::string RemoveFileType(std::string a_Name);
		std::string AbstractFileNameFromPath(std::string a_Path);
		std::string AbstractFolderFromPath(std::string a_Path);
		EFileType GetFileType(std::string a_FileName);
	};
}