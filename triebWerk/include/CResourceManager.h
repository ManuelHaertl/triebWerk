#pragma once
#include <string>
#include <vector>
#include <Windows.h>
#include <unordered_map>
#include <d3d11.h>

#include <CGraphics.h>
#include <EFileType.h>
#include <CTilesetMap.h>
#include <CTMXParser.h>
#include <CStringHasher.h>
#include <CINIParser.h>
#include <CTexture2D.h>
#include <COBJParser.h>
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

		//Texture2D
		typedef std::unordered_map<size_t, CTexture2D*> CTextureMap;
		typedef std::pair<size_t, CTexture2D*> CTexturePair;

		//OBJ 
		typedef std::unordered_map<size_t, CMesh*> CMeshMap;
		typedef std::pair<size_t, CMesh*> CMeshPair;

	private:
		CTilesetHashMap m_TilesetBuffer;
		CConfigurationMap m_ConfigurationBuffer;
		CTextureMap m_TextureBuffer;
		CMeshMap m_MeshBuffer;

		CGraphics* m_pGraphicsHandle;

		std::string m_ModulPath;

	public:
		CResourceManager();
		~CResourceManager();

	public:
		bool Initialize(CGraphics* a_pGraphics);
		void CleanUp();
		
		const char& GetModulPath();

		//Bind D3D11 Resources new
		//For example if the backbuffer was resized
		void UpdateD3D11Resources();

		//Load Interface User
		void LoadAllFilesInFolder(const char* a_pPath);
		void LoadAllSpecificFilesInFolder(EFileType a_FileType, const char* a_pPath);
		void LoadSpecificFile(const char* a_pPath);

		//Get Interface
		CTilesetMap* GetTileset(const char* a_pTilesetName);
        std::vector<CTilesetMap*> GetAllTilesets();
		CConfiguration* GetConfiguration(const char* a_pConfigurationName);
		CTexture2D* GetTexture2D(const char* a_pTexture2DName);
		CMesh* GetMesh(const char* a_pMeshName);

		//Unload
		void UnloadTileset(const char* a_pTilesetName);
		void UnloadConfiguration(const char* a_pConfigurationName);
		void UnloadTexture2D(const char* a_pTexture2DName);
		void UnloadMesh(const char* a_pMeshName);

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