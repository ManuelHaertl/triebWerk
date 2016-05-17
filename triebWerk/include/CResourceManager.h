#pragma once
#include <string>
#include <vector>
#include <Windows.h>
#include <unordered_map>
#include <d3d11.h>
#include <assert.h>

#include <CGraphics.h>
#include <EFileType.h>
#include <CTilesetMap.h>
#include <CTMXParser.h>
#include <CStringHasher.h>
#include <CTWFParser.h>
#include <CTexture2D.h>
#include <COBJParser.h>
#include <CHLSLParser.h>
#include <CFileWatcher.h>
#include <CMaterial.h>
#include <loadPNG\lodepng.h>
#include <CDebugLogfile.h>

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

		//TWF - triebWerk Format
		typedef std::unordered_map<size_t, CTWFData*> CTWFDataMap;
		typedef std::pair<size_t, CTWFData*> CTWFDataPair;

		//Texture2D
		typedef std::unordered_map<size_t, CTexture2D*> CTextureMap;
		typedef std::pair<size_t, CTexture2D*> CTexturePair;

		//OBJ 
		typedef std::unordered_map<size_t, CMesh*> CMeshMap;
		typedef std::pair<size_t, CMesh*> CMeshPair;

		//Material
		typedef std::unordered_map<size_t, CMaterial*> CMaterialMap;
		typedef std::pair<size_t, CMaterial*> CMaterialPair;

	private:
		CFileWatcher m_FileWatcher;
		CTilesetHashMap m_TilesetBuffer;
		CTWFDataMap m_TWFBuffer;
		CTextureMap m_TextureBuffer;
		CMeshMap m_MeshBuffer;
		CMaterialMap m_MaterialBuffer;

		CGraphics* m_pGraphicsHandle;

		std::string m_ModulPath;

	public:
		CResourceManager();
		~CResourceManager();

	public:
		bool Initialize(CGraphics* a_pGraphics);
		void CleanUp();
		void Update();

		const char* GetModulPath();

		//Load Interface User

		//Load all files supported in a specific directory and subdirectory
		void LoadAllFilesInFolder(const char* a_pPath);

		//Loads only the EFileType in a specific directory and subdirectory
		void LoadAllSpecificFilesInFolder(EFileType a_FileType, const char* a_pPath);

		//Loads only the one file specified in the path
		void LoadSpecificFile(const char* a_pPath);

		//Get Interface
		CTilesetMap* GetTileset(const char* a_pTilesetName);
		CTWFData* GetTWFData(const char* a_pConfigurationName);
		CTexture2D* GetTexture2D(const char* a_pTexture2DName);
		CMesh* GetMesh(const char* a_pMeshName);
		CMaterial* GetMaterial(const char* a_pMaterialName);

		//Get all data in this directory and subdirectory which were previous loaded 
		template<typename T>
		void GetAll(const char* a_pPath, std::vector<T*>* a_pOutData);

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
		void LoadTWF(SFile a_File);

		bool SetModulPath();
		std::vector<SFile> SearchFolderForAllFiles(const char* a_FolderToLoad);

		//String helper functions
		bool CompareFileTypes(const std::string& a_Name, const char* a_ExpectedType);
		std::string RemoveFileType(const std::string& a_Name);
		std::string AbstractFileNameFromPath(const std::string& a_Path);
		std::string AbstractFolderFromPath(const std::string& a_Path);
		EFileType GetFileType(const std::string& a_FileName);

		//If a Filewatcher event occures, load resource new and replace the previous one 
		void UpdateResourceChanges();
	};
}

//Template Implementions
#include "../src/CResourceManager.hpp"