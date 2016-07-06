#include <CResourceManager.h>

triebWerk::CResourceManager::CResourceManager() :
	m_pGraphicsHandle(nullptr)
{
}

triebWerk::CResourceManager::~CResourceManager()
{
}

bool triebWerk::CResourceManager::Initialize(CGraphics* a_pGraphics, FT_Library* a_pFontLibrary, CSoundEngine* a_pSoundEngine)
{
	//bool error = SetModulPath();
	m_pGraphicsHandle = a_pGraphics;
    m_pFontLibraryHandle = a_pFontLibrary;
	m_pSoundEngineHandle = a_pSoundEngine;

#ifdef _DEBUG
	m_FileWatcher.Watch("data", true);
#endif //DEBUG
	//return error;

	LoadAllFilesInFolder("data/Default/");

    return true;
}

void triebWerk::CResourceManager::CleanUp()
{
	for (auto Tileset : m_TilesetBuffer)
	{
		Tileset.second->ClearMap();
		delete Tileset.second;
	}

	for (auto config : m_TWFBuffer)
	{
		delete config.second;
	}

	for (auto mesh : m_MeshBuffer)
	{
		mesh.second->m_pVertexBuffer->Release();
		delete mesh.second->m_pVertices;
		delete mesh.second;
	}

	for (auto texture : m_TextureBuffer)
	{
		texture.second->GetD3D11Texture()->Release();
		texture.second->GetShaderResourceView()->Release();
		delete texture.second;
	}

	for (const auto& material : m_MaterialBuffer)
	{
		material.second->m_pVertexShader.m_pD3DVertexShader->Release();
		material.second->m_pPixelShader.m_pD3DPixelShader->Release();
		if (material.second->m_pGeometryShader.m_pD3DGeometryShader != nullptr)
			material.second->m_pGeometryShader.m_pD3DGeometryShader->Release();

		delete material.second;
	}

    for (auto font : m_FontBuffer)
    {
        delete font.second;
    }

	for (auto sound : m_SoundBuffer)
	{
		delete sound.second;
	}

	m_TWFBuffer.clear();
	m_TextureBuffer.clear();
	m_TilesetBuffer.clear();
	m_MeshBuffer.clear();
	m_MaterialBuffer.clear();
    m_FontBuffer.clear();

	m_FileWatcher.StopWatching();
}

void triebWerk::CResourceManager::Update()
{
#ifdef _DEBUG
	UpdateResourceChanges();
#endif // DEBUG
}

const char* triebWerk::CResourceManager::GetModulPath()
{
	return m_ModulPath.c_str();
}

void triebWerk::CResourceManager::LoadAllFilesInFolder(const char * a_pPath)
{
	DebugLogfile.LogfText(CDebugLogfile::ELogType::Text, false, ":::::::::::::::::::::: LoadAllFilesInFolder ::::::::::::::::::::::");

	std::vector<SFile> filesToLoad = SearchFolderForAllFiles(a_pPath);

	for(auto file : filesToLoad)
	{
		LoadFile(file);
	}

	DebugLogfile.LogfText(CDebugLogfile::ELogType::Text, false, ":::::::::::::::::::::: Finish ::::::::::::::::::::::");
}

void triebWerk::CResourceManager::LoadAllSpecificFilesInFolder(EFileType a_FileType, const char * a_pPath)
{
	std::vector<SFile> filesToLoad = SearchFolderForAllFiles(a_pPath);

	for (auto file : filesToLoad)
	{
		if (file.FileType == a_FileType)
		{
			LoadFile(file);
		}
	}
}

void triebWerk::CResourceManager::LoadSpecificFile(const char * a_pPath)
{
	SFile fileToLoad;
	fileToLoad.FileType = GetFileType(a_pPath);
	fileToLoad.FilePath = m_ModulPath + a_pPath;
	fileToLoad.FileName = AbstractFileNameFromPath(a_pPath);

	LoadFile(fileToLoad);
}

triebWerk::CTilesetMap * triebWerk::CResourceManager::GetTileset(const char * TilesetName)
{
	auto foundIterator = m_TilesetBuffer.find(StringHasher(RemoveFileType(TilesetName)));

	if (foundIterator == m_TilesetBuffer.end())
	{
		DebugLogfile.LogfText(CDebugLogfile::ELogType::Warning, false, "Warning: No Tileset was loaded with the Name: %s", TilesetName);
		return nullptr;
	}
	else
	{
		return foundIterator->second;
	}
}

triebWerk::CTWFData* triebWerk::CResourceManager::GetTWFData(const char * a_pConfiguration)
{
	auto foundIterator = m_TWFBuffer.find(StringHasher(RemoveFileType(a_pConfiguration)));

	if (foundIterator == m_TWFBuffer.end())
	{
		DebugLogfile.LogfText(CDebugLogfile::ELogType::Warning, false, "Warning: No TWF was loaded with the Name: %s", a_pConfiguration);
		return nullptr;
	}
	else
	{
		return foundIterator->second;
	}
}

triebWerk::CTexture2D * triebWerk::CResourceManager::GetTexture2D(const char * a_pTexture2DName)
{
	auto foundIterator = m_TextureBuffer.find(StringHasher(RemoveFileType(a_pTexture2DName)));

	if (foundIterator == m_TextureBuffer.end())
	{
		DebugLogfile.LogfText(CDebugLogfile::ELogType::Warning, false, "Warning: No Texture2D was loaded with the Name: %s", a_pTexture2DName);
		return nullptr;
	}
	else
	{
		return foundIterator->second;
	}
}

triebWerk::CMesh * triebWerk::CResourceManager::GetMesh(const char * a_pMeshName)
{
	auto foundIterator = m_MeshBuffer.find(StringHasher(RemoveFileType(a_pMeshName)));

	if (foundIterator == m_MeshBuffer.end())
	{
		DebugLogfile.LogfText(CDebugLogfile::ELogType::Warning, false, "Warning: No Mesh was loaded with the Name: %s", a_pMeshName);
		return nullptr;
	}
	else
	{
		return foundIterator->second;
	}
}

triebWerk::CMaterial* triebWerk::CResourceManager::GetMaterial(const char * a_pEffectName)
{
	auto foundIterator = m_MaterialBuffer.find(StringHasher(RemoveFileType(a_pEffectName)));

	if (foundIterator == m_MaterialBuffer.end())
	{
		DebugLogfile.LogfText(CDebugLogfile::ELogType::Warning, false, "Warning: No Material was loaded with the Name: %s", a_pEffectName);
		return nullptr;
	}
	else
	{
		return foundIterator->second;
	}
}

triebWerk::CFontFace* triebWerk::CResourceManager::GetFontFace(const char* a_pFontName)
{
    auto foundIterator = m_FontBuffer.find(StringHasher(RemoveFileType(a_pFontName)));

    if (foundIterator == m_FontBuffer.end())
    {
        DebugLogfile.LogfText(CDebugLogfile::ELogType::Warning, false, "Warning: No Font was loaded with the Name: %s", a_pFontName);
        return nullptr;
    }
    else
    {
        return foundIterator->second;
    }
}

triebWerk::CSound * triebWerk::CResourceManager::GetSound(const char * a_pSoundName)
{
	auto foundIterator = m_SoundBuffer.find(StringHasher(RemoveFileType(a_pSoundName)));

	if (foundIterator == m_SoundBuffer.end())
	{
		DebugLogfile.LogfText(CDebugLogfile::ELogType::Warning, false, "Warning: No Font was loaded with the Name: %s", a_pSoundName);
		return nullptr;
	}
	else
	{
		return foundIterator->second;
	}
}

void triebWerk::CResourceManager::UnloadTileset(const char * a_pTilesetName)
{
	auto foundIterator = m_TilesetBuffer.find(StringHasher(RemoveFileType(a_pTilesetName)));

	if (foundIterator == m_TilesetBuffer.end())
	{
		return;
	}
	else
	{
		foundIterator->second->ClearMap();
		delete foundIterator->second;
		m_TilesetBuffer.erase(StringHasher(RemoveFileType(a_pTilesetName)));
	}
}

void triebWerk::CResourceManager::UnloadConfiguration(const char * a_pConfigurationName)
{
	auto foundIterator = m_TWFBuffer.find(StringHasher(RemoveFileType(a_pConfigurationName)));

	if (foundIterator == m_TWFBuffer.end())
	{
		return;
	}
	else
	{
		delete foundIterator->second;
		m_TWFBuffer.erase(StringHasher(RemoveFileType(a_pConfigurationName)));
	}
}

void triebWerk::CResourceManager::UnloadTexture2D(const char * a_pTexture2DName)
{
	auto foundIterator = m_TextureBuffer.find(StringHasher(RemoveFileType(a_pTexture2DName)));

	if (foundIterator == m_TextureBuffer.end())
	{
		return;
	}
	else
	{
		foundIterator->second->GetD3D11Texture()->Release();
		foundIterator->second->GetShaderResourceView()->Release();
		delete foundIterator->second;

		m_TextureBuffer.erase(StringHasher(RemoveFileType(a_pTexture2DName)));
	}
}

void triebWerk::CResourceManager::UnloadMesh(const char * a_pMeshName)
{
	auto foundIterator = m_MeshBuffer.find(StringHasher(RemoveFileType(a_pMeshName)));

	if (foundIterator == m_MeshBuffer.end())
	{
		return;
	}
	else
	{
		foundIterator->second->m_pVertexBuffer->Release();
		//delete foundIterator->second->m_pVertices;
		delete foundIterator->second;
		m_MeshBuffer.erase(StringHasher(RemoveFileType(a_pMeshName)));
	}
}

void triebWerk::CResourceManager::LoadFile(SFile a_File)
{


	switch (a_File.FileType)
	{
	case EFileType::HLSL:
		LoadHLSL(a_File);
		DebugLogfile.LogfText(CDebugLogfile::ELogType::Text, false, "Start loading file: %s", a_File.FilePath.c_str());
		break;
	case EFileType::TWF:
		LoadTWF(a_File);
		DebugLogfile.LogfText(CDebugLogfile::ELogType::Text, false, "Start loading file: %s", a_File.FilePath.c_str());
		break;
	case EFileType::MP3:
	case EFileType::FLAC:
	case EFileType::WAV:
	case EFileType::OGG:
	case EFileType::MOD:
	case EFileType::XM:
		LoadAudio(a_File);
		DebugLogfile.LogfText(CDebugLogfile::ELogType::Text, false, "Start loading file: %s", a_File.FilePath.c_str());
		break;
	case EFileType::OBJ:
		LoadOBJ(a_File);
		DebugLogfile.LogfText(CDebugLogfile::ELogType::Text, false, "Start loading file: %s", a_File.FilePath.c_str());
		break;
	case EFileType::PNG:
		LoadPNG(a_File);
		DebugLogfile.LogfText(CDebugLogfile::ELogType::Text, false, "Start loading file: %s", a_File.FilePath.c_str());
		break;
	case EFileType::DDS:
		LoadDDS(a_File);
		DebugLogfile.LogfText(CDebugLogfile::ELogType::Text, false, "Start loading file: %s", a_File.FilePath.c_str());
		break;
	case EFileType::TMX:
		LoadTMX(a_File);
		DebugLogfile.LogfText(CDebugLogfile::ELogType::Text, false, "Start loading file: %s", a_File.FilePath.c_str());
		break;
	case EFileType::TTF:
	case EFileType::OTF:
		LoadFont(a_File);
		DebugLogfile.LogfText(CDebugLogfile::ELogType::Text, false, "Start loading file: %s", a_File.FilePath.c_str());
		break;
	}
}

void triebWerk::CResourceManager::LoadPNG(SFile a_File)
{
	size_t hash = StringHasher(RemoveFileType(a_File.FileName));
	if (ExistsResourceInBuffer(EFileType::PNG, hash))
		return;


	//PixelBuffer
	std::vector<unsigned char> imageBuffer;

	unsigned int width;
	unsigned int height;

	unsigned int error = lodepng::decode(imageBuffer, width, height, a_File.FilePath);

	if (error != 0)
	{
		DebugLogfile.LogfText(CDebugLogfile::ELogType::Warning, false, "Warning: PNG could not be loaded! File: %s", a_File.FilePath.c_str());
		return;
	}
	else
	{
		//Create Texture and load it on the graphics card
		CTexture2D* texture = new CTexture2D();

		ID3D11Texture2D* d3dtexture = m_pGraphicsHandle->CreateD3D11Texture2D(&imageBuffer[0], width, height);

		ID3D11ShaderResourceView* resourceView = m_pGraphicsHandle->CreateID3D11ShaderResourceView(d3dtexture);

		texture->SetTexture(width, height, d3dtexture, resourceView);

		m_TextureBuffer.insert(CTexturePair(hash, texture));
	}

}

void triebWerk::CResourceManager::LoadOBJ(SFile a_File)
{
	size_t hash = StringHasher(RemoveFileType(a_File.FileName));
	if (ExistsResourceInBuffer(EFileType::OBJ, hash))
		return;

	COBJParser objParser;
	bool success = objParser.LoadOBJ(a_File.FilePath.c_str());

	if (!success)
	{
		DebugLogfile.LogfText(CDebugLogfile::ELogType::Warning, false, "Warning: OBJ could not be loaded! File: %s", a_File.FilePath.c_str());
		return;
	}

	CMesh* mesh = new CMesh();
	mesh->m_pVertices = new CMesh::SVertex[objParser.m_VertexCount];
	mesh->m_VertexCount = objParser.m_VertexCount;
	
	memcpy(mesh->m_pVertices, objParser.m_pVertices, sizeof(CMesh::SVertex) * objParser.m_VertexCount);

	mesh->m_IndexCount = objParser.m_IndexCount;
	mesh->m_pVertexBuffer = m_pGraphicsHandle->CreateVertexBuffer(mesh->m_pVertices, mesh->m_VertexCount);
	mesh->m_pIndexBuffer = m_pGraphicsHandle->CreateIndexBuffer(objParser.m_pIndices, sizeof(unsigned int) * objParser.m_IndexCount);

	m_MeshBuffer.insert(CMeshPair(hash, mesh));
}

void triebWerk::CResourceManager::LoadAudio(SFile a_File)
{
	size_t hash = StringHasher(RemoveFileType(a_File.FileName));
	if (ExistsResourceInBuffer(EFileType::MP3, hash))
		return;

	CSound* sound = new CSound;
	
	sound->m_SoundType = CSound::ESoundType::SFX;
	sound->m_pSoundSource = this->m_pSoundEngineHandle->m_pDevice->addSoundSourceFromFile(a_File.FilePath.c_str());
	if (sound->m_pSoundSource == nullptr)
	{
		DebugLogfile.LogfText(CDebugLogfile::ELogType::Warning, false, "Warning: MP3 could not be loaded! File: %s", a_File.FilePath.c_str());
		delete sound;
		return;
	}

	//sound->m_pSoundSource->setDefaultVolume(CConfigManager::Instance().m_Config.m_SFXVolume);

	sound->m_SoundID.SetName(a_File.FileName);

	m_SoundBuffer.insert(CSoundPair(hash, sound));
}

void triebWerk::CResourceManager::LoadTMX(SFile a_File)
{
	size_t hash = StringHasher(RemoveFileType(a_File.FileName));
	if (ExistsResourceInBuffer(EFileType::TMX, hash))
		return;

	CTMXParser parserTMX = CTMXParser();
	CTilesetMap* tileset = new CTilesetMap();
	bool success = parserTMX.ParseData(a_File.FilePath.c_str(), tileset);

	if (!success)
	{
		DebugLogfile.LogfText(CDebugLogfile::ELogType::Warning, false, "Warning: TMX could not be loaded! File: %s", a_File.FilePath.c_str());
		delete tileset;
		return;
	}

	m_TilesetBuffer.insert(CTilesetPair(hash, tileset));
}

void triebWerk::CResourceManager::LoadHLSL(SFile a_File)
{
	size_t hash = StringHasher(RemoveFileType(a_File.FileName));
	if (ExistsResourceInBuffer(EFileType::HLSL, hash))
		return;

	CMaterial* temp = new CMaterial();
	CHLSLParser hlslParser;
	bool success = hlslParser.ParseShader(a_File.FilePath.c_str(), m_pGraphicsHandle, temp);

	if (!success)
	{
		delete temp;
		return;
	}

	m_MaterialBuffer.insert(CMaterialPair(hash, temp));
}

void triebWerk::CResourceManager::LoadTWF(SFile a_File)
{
	size_t hash = StringHasher(RemoveFileType(a_File.FileName));
	if (ExistsResourceInBuffer(EFileType::TWF, hash))
		return;

	CTWFParser twfParser;
	CTWFData* twfData = new CTWFData();
	twfParser.ParseData(a_File.FilePath.c_str(), twfData);
	
	m_TWFBuffer.insert(CTWFDataPair(hash, twfData));
}

void triebWerk::CResourceManager::LoadFont(SFile a_File)
{
	size_t hash = StringHasher(RemoveFileType(a_File.FileName));
	if (ExistsResourceInBuffer(EFileType::TTF, hash))
		return;

    CFontFace* pFontFace = new CFontFace(m_pFontLibraryHandle, a_File.FilePath.c_str(), a_File.FileName.c_str());

	//Insert Data in font map
    m_FontBuffer.insert(CFontPair(hash, pFontFace));
}

void triebWerk::CResourceManager::LoadDDS(SFile a_File)
{
	size_t hash = StringHasher(RemoveFileType(a_File.FileName));
	if (ExistsResourceInBuffer(EFileType::DDS, hash))
		return;

	ID3D11Texture2D* pTexture = nullptr;
	ID3D11ShaderResourceView* pShaderResource = nullptr;
	ID3D11Resource* pResource = nullptr;

	const size_t cSize = strlen(a_File.FilePath.c_str()) + 1;
	wchar_t* wc = new wchar_t[cSize];
	size_t numberOfChars;
	mbstowcs_s(&numberOfChars, wc, cSize, a_File.FilePath.c_str(), cSize); //wc, a_File.FilePath.c_str(), cSize);

	HRESULT hr = DirectX::CreateDDSTextureFromFile(m_pGraphicsHandle->GetDevice(), wc, nullptr, &pShaderResource);
	delete wc;

	if (FAILED(hr))
	{
		DebugLogfile.LogfText(CDebugLogfile::ELogType::Warning, false, "Warning: DDS could not be loaded! File: %s", a_File.FilePath.c_str());
		return;
	}

	CTexture2D* ptwTexture = new CTexture2D();


	pShaderResource->GetResource(&pResource);
	pTexture = static_cast<ID3D11Texture2D*>(pResource);

	D3D11_TEXTURE2D_DESC textureDesc;

	pTexture->GetDesc(&textureDesc);

	ptwTexture->SetTexture(textureDesc.Width, textureDesc.Height, pTexture, pShaderResource);

	m_TextureBuffer.insert(CTexturePair(hash, ptwTexture));
}

bool triebWerk::CResourceManager::SetModulPath()
{
	char modulFilePath[MAX_PATH] = "";
	if (GetModuleFileNameA(NULL, modulFilePath, MAX_PATH) == 0)
		return false;

	m_ModulPath = modulFilePath;
	m_ModulPath.resize(m_ModulPath.rfind("\\") + 1);

	return true;
}

std::vector<triebWerk::CResourceManager::SFile> triebWerk::CResourceManager::SearchFolderForAllFiles(const char * a_FolderToLoad)
{
	WIN32_FIND_DATA winFindData;
	HANDLE hFindHandle = INVALID_HANDLE_VALUE;

	//Build Directory String
	std::string dir = m_ModulPath;
	dir += a_FolderToLoad;
	dir += "\\";

	//Build Search Directory String
	std::string SearchFolderForAllFiles = dir;
	SearchFolderForAllFiles += "*";

	std::vector<SFile>filesToLoad; 
	filesToLoad.clear();
	//Find first Element in Directory
	hFindHandle = FindFirstFile(SearchFolderForAllFiles.c_str(), &winFindData);

	std::vector<std::string>directories;

	if (INVALID_HANDLE_VALUE == hFindHandle)
	{
		//DebugLogfile.LogfText(Debug.m_Logfile.Error, false, "Folder not found! Name: %s", a_FolderToLoad);
		return filesToLoad;
	}

	//Search for Files and Directories
	do
	{
		if (winFindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			if (strcmp(winFindData.cFileName, ".") != 0 && strcmp(winFindData.cFileName, "..") != 0)
			{
				std::string directoryPath = a_FolderToLoad;
				directoryPath += "\\";
				directoryPath += winFindData.cFileName;
				directories.push_back(directoryPath);
			}
		}
		else
		{
			SFile file;
			file.FileName = winFindData.cFileName;
			file.FilePath = dir + winFindData.cFileName;
			file.FileType = GetFileType(file.FileName);

			filesToLoad.push_back(file);
		}
	} while (FindNextFileA(hFindHandle, &winFindData) != 0);

	//Serach All Files in Subdirectories
	for (auto directory : directories)
	{
		std::vector<SFile> filesInDirectory = this->SearchFolderForAllFiles(directory.c_str());

		for (auto file : filesInDirectory)
		{
			filesToLoad.push_back(file);
		}
	}

	return filesToLoad;
}

bool triebWerk::CResourceManager::ExistsResourceInBuffer(EFileType a_FileType, size_t a_Hash)
{
	switch (a_FileType)
	{
	case triebWerk::EFileType::PNG:
	{
		auto iter = m_TextureBuffer.find(a_Hash);

		if (iter != m_TextureBuffer.end())
			return true;
		else
			return false;
	}break;
		

	case triebWerk::EFileType::OBJ:
	{
		auto iter = m_MeshBuffer.find(a_Hash);

		if (iter != m_MeshBuffer.end())
			return true;
		else
			return false;
	}break;
	//case triebWerk::EFileType::MP3:
	//{
	//	auto iter = m_TextureBuffer.find(a_Hash);

	//	if (iter != m_TextureBuffer.end())
	//		return true;
	//	else
	//		return false;
	//}break;
	case triebWerk::EFileType::TMX:
	{
		auto iter = m_TilesetBuffer.find(a_Hash);

		if (iter != m_TilesetBuffer.end())
			return true;
		else
			return false;
	}break;
	case triebWerk::EFileType::HLSL:
	{
		auto iter = m_MaterialBuffer.find(a_Hash);

		if (iter != m_MaterialBuffer.end())
			return true;
		else
			return false;
	}break;
	case triebWerk::EFileType::TWF:
	{
		auto iter = m_TWFBuffer.find(a_Hash);

		if (iter != m_TWFBuffer.end())
			return true;
		else
			return false;
	}break;
	case triebWerk::EFileType::TTF:
	case triebWerk::EFileType::OTF:
	{
		auto iter = m_FontBuffer.find(a_Hash);

		if (iter != m_FontBuffer.end())
			return true;
		else
			return false;
	}break;
	}

	return false;
}

bool triebWerk::CResourceManager::CompareFileTypes(const std::string& a_Name, const char * a_ExpectedType)
{
	size_t fileExtensionPosition = a_Name.find(".");
	if (fileExtensionPosition == std::string::npos)
		return false;

	int isSame = a_Name.compare(fileExtensionPosition, std::string::npos, a_ExpectedType);
	if (isSame == 0)
		return true;

	return false;
}

std::string triebWerk::CResourceManager::RemoveFileType(const std::string& a_Name)
{
	return a_Name.substr(0, a_Name.find("."));
}

std::string triebWerk::CResourceManager::AbstractFileNameFromPath(const std::string& a_Path)
{
	return a_Path.substr(a_Path.rfind("\\") + 1, a_Path.size() - a_Path.rfind("\\") + 1);
}

std::string triebWerk::CResourceManager::AbstractFolderFromPath(const std::string& a_Path)
{
	size_t end = a_Path.rfind("/", a_Path.rfind("/"));
	size_t start = a_Path.rfind("/", a_Path.rfind("/") - 1) + 1;
	return a_Path.substr(start, end - start);
}

triebWerk::EFileType triebWerk::CResourceManager::GetFileType(const std::string& a_FileName)
{
	size_t fileExtensionPosition = a_FileName.find(".");

	if (fileExtensionPosition == std::string::npos)
		return EFileType::NONE;

	std::string fileType = a_FileName.substr(fileExtensionPosition, a_FileName.size() - fileExtensionPosition);

	if (fileType == ".twf")
	{
		return EFileType::TWF;
	}
	else if(fileType == ".hlsl")
	{
		return EFileType::HLSL;
	}
	else if (fileType == ".mp3")
	{
		return EFileType::MP3;
	}
	else if (fileType == ".wav")
	{
		return EFileType::WAV;
	}
	else if (fileType == ".ogg")
	{
		return EFileType::OGG;
	}
	else if (fileType == ".flac")
	{
		return EFileType::FLAC;
	}
	else if (fileType == ".mod")
	{
		return EFileType::MOD;
	}
	else if (fileType == ".xm")
	{
		return EFileType::XM;
	}
	else if (fileType == ".obj")
	{
		return EFileType::OBJ;
	}
	else if (fileType == ".png")
	{
		return EFileType::PNG;
	}
	else if (fileType == ".tmx")
	{
		return EFileType::TMX;
	}
	else if (fileType == ".ttf")
	{
		return EFileType::TTF;
	}
	else if (fileType == ".dds")
	{
		return EFileType::DDS;
	}

	return EFileType::NONE;
}

void triebWerk::CResourceManager::UpdateResourceChanges()
{
	//Get the events from FileWatcher
	std::vector<CFileWatcher::SFileEvent> events;
	m_FileWatcher.GetLastestEvents(&events);

	//iterate over all events
	for (size_t i = 0; i < events.size(); i++)
	{
		//if the event type is supported and a existing file was modified reload the data
		EFileType type = GetFileType(events[i].FileName);
		switch (type)
		{

		case EFileType::PNG:
		{
			if (events[i].Event == CFileWatcher::EFileEventTypes::Modified)
			{
				//Create a the PNGFile to load
				SFile fileToLoad;
				fileToLoad.FileName = AbstractFileNameFromPath(events[0].FileName);
				fileToLoad.FilePath = m_FileWatcher.m_PathWatching + "\\" + events[0].FileName;
				fileToLoad.FileType = EFileType::PNG;

				//Load and update the texture
				CTexture2D* texture = GetTexture2D(fileToLoad.FileName.c_str());
				if (texture != nullptr)
				{
					std::vector<unsigned char> imageBuffer;

					unsigned int width;
					unsigned int height;

					unsigned int error = lodepng::decode(imageBuffer, width, height, fileToLoad.FilePath);

					if (error != 0)
						return;
					else
					{
						ID3D11Texture2D* d3dtexture = m_pGraphicsHandle->CreateD3D11Texture2D(&imageBuffer[0], width, height);

						ID3D11ShaderResourceView* resourceView = m_pGraphicsHandle->CreateID3D11ShaderResourceView(d3dtexture);

						texture->SetTexture(width, height, d3dtexture, resourceView);
					}
				}
			}	
		}break;

		case EFileType::OBJ:
		{
			if (events[i].Event == CFileWatcher::EFileEventTypes::Modified)
			{
				//Create the OBJFile to load 
				SFile fileToLoad;
				fileToLoad.FileName = AbstractFileNameFromPath(events[i].FileName);
				fileToLoad.FilePath = m_FileWatcher.m_PathWatching + "\\" + events[0].FileName;
				fileToLoad.FileType = EFileType::OBJ;

				//Is the Mesh in the ResourceManager
				CMesh* meshIn = GetMesh(fileToLoad.FileName.c_str());
				if (meshIn != nullptr)
				{
					//Parse the modifed Mesh
					COBJParser objParser;


					if (objParser.LoadOBJ(fileToLoad.FilePath.c_str()))
					{
						//Release the old Mesh
						meshIn->m_pIndexBuffer->Release();
						meshIn->m_pVertexBuffer->Release();
						delete meshIn->m_pVertices;
						meshIn->m_pVertices = nullptr;
						meshIn->m_pIndexBuffer = nullptr;
						meshIn->m_pVertexBuffer = nullptr;

						//Create the new Mesh
						meshIn->m_IndexCount = objParser.m_IndexCount;
						meshIn->m_VertexCount = objParser.m_VertexCount;
						meshIn->m_pVertices = new CMesh::SVertex[objParser.m_VertexCount];
						std::cout << fileToLoad.FilePath << std::endl;
						std::cout << meshIn->m_VertexCount << std::endl;
						std::cout << meshIn->m_IndexCount << std::endl;
						memcpy(meshIn->m_pVertices, objParser.m_pVertices, sizeof(CMesh::SVertex) * objParser.m_VertexCount);

						meshIn->m_pVertexBuffer = m_pGraphicsHandle->CreateVertexBuffer(meshIn->m_pVertices, meshIn->m_VertexCount);
						meshIn->m_pIndexBuffer = m_pGraphicsHandle->CreateIndexBuffer(objParser.m_pIndices, sizeof(unsigned int) * objParser.m_IndexCount);
					}
				}
			}
		}break;

		case EFileType::TWF:
		{
			if (events[i].Event == CFileWatcher::EFileEventTypes::Modified)
			{
				//Create the TWFFile to load 
				SFile fileToLoad;
				fileToLoad.FileName = AbstractFileNameFromPath(events[i].FileName);
				fileToLoad.FilePath = m_FileWatcher.m_PathWatching + "\\" + events[0].FileName;
				fileToLoad.FileType = EFileType::TWF;

				CTWFData* data = GetTWFData(fileToLoad.FileName.c_str());

				if (data != nullptr)
				{
					//Clear the old data
					data->m_ConfigurationTable.clear();
#
					//Fill twfData with the updated values
					CTWFParser twfParser;
					twfParser.ParseData(fileToLoad.FilePath.c_str(), data);
					data->m_IsModified = true;
				}
			}
		}break;

		case EFileType::TMX:
		{
			if (events[i].Event == CFileWatcher::EFileEventTypes::Modified)
			{
				//Create the TWFFile to load 
				SFile fileToLoad;
				std::string t = events[i].FileName;
				fileToLoad.FileName = AbstractFileNameFromPath(events[i].FileName);
				fileToLoad.FilePath = m_FileWatcher.m_PathWatching + "\\" + t;
				fileToLoad.FileType = EFileType::TMX;

				CTMXParser parser;

				//Is the tileset in memory 
				CTilesetMap* pTilesetMap = GetTileset(fileToLoad.FileName.c_str());
				
				if (pTilesetMap != nullptr)
				{
					//Clear the old data
					pTilesetMap->ClearMap();

					//Load the new data
					bool success = parser.ParseData(fileToLoad.FilePath.c_str(), pTilesetMap);

					if (success)
					{
						pTilesetMap->m_Modified = true;
					}
				}
			}
		}break;

		case EFileType::DDS:
		{
			if (events[i].Event == CFileWatcher::EFileEventTypes::Modified)
			{
				//Create a the PNGFile to load
				SFile fileToLoad;
				fileToLoad.FileName = AbstractFileNameFromPath(events[0].FileName);
				fileToLoad.FilePath = m_FileWatcher.m_PathWatching + "\\" + events[0].FileName;
				fileToLoad.FileType = EFileType::DDS;

				//Load and update the texture
				CTexture2D* texture = GetTexture2D(fileToLoad.FileName.c_str());
				if (texture != nullptr)
				{
				/*	std::vector<unsigned char> imageBuffer;

					unsigned int width;
					unsigned int height;

					unsigned int error = lodepng::decode(imageBuffer, width, height, fileToLoad.FilePath);

					if (error != 0)
						return;*/

					ID3D11Texture2D* pTexture = nullptr;
					ID3D11ShaderResourceView* pShaderResource = nullptr;
					ID3D11Resource* pResource = nullptr;

					const size_t cSize = strlen(fileToLoad.FilePath.c_str()) + 1;
					wchar_t* wc = new wchar_t[cSize];
					size_t numberOfChars;
					mbstowcs_s(&numberOfChars, wc, cSize, fileToLoad.FilePath.c_str(), cSize); //wc, a_File.FileP

					HRESULT hr = DirectX::CreateDDSTextureFromFile(m_pGraphicsHandle->GetDevice(), wc, nullptr, &pShaderResource);
						delete wc;

					if (FAILED(hr))
					{
						DebugLogfile.LogfText(CDebugLogfile::ELogType::Warning, false, "Warning: DDS could not be reloaded in filewatcher! File: %s", fileToLoad.FilePath.c_str());
						break;
					}

					pShaderResource->GetResource(&pResource);
					pTexture = static_cast<ID3D11Texture2D*>(pResource);

					D3D11_TEXTURE2D_DESC textureDesc;

					pTexture->GetDesc(&textureDesc);

					texture->SetTexture(textureDesc.Width, textureDesc.Height, pTexture, pShaderResource);
				}
			}
		}break;
		}
	}

	events.clear();
}

//size_t hash = StringHasher(RemoveFileType(a_File.FileName));
//if (ExistsResourceInBuffer(EFileType::DDS, hash))
//return;
//
//ID3D11Texture2D* pTexture = nullptr;
//ID3D11ShaderResourceView* pShaderResource = nullptr;
//ID3D11Resource* pResource = nullptr;
//
//const size_t cSize = strlen(a_File.FilePath.c_str()) + 1;
//wchar_t* wc = new wchar_t[cSize];
//size_t numberOfChars;
//mbstowcs_s(&numberOfChars, wc, cSize, a_File.FilePath.c_str(), cSize); //wc, a_File.FilePath.c_str(), cSize);
//
//HRESULT hr = DirectX::CreateDDSTextureFromFile(m_pGraphicsHandle->GetDevice(), wc, nullptr, &pShaderResource);
//delete wc;
//
//if (FAILED(hr))
//{
//	DebugLogfile.LogfText(CDebugLogfile::ELogType::Warning, false, "Warning: DDS could not be loaded! File: %s", a_File.FilePath.c_str());
//	return;
//}
//
//CTexture2D* ptwTexture = new CTexture2D();
//
//
//pShaderResource->GetResource(&pResource);
//pTexture = static_cast<ID3D11Texture2D*>(pResource);
//
//D3D11_TEXTURE2D_DESC textureDesc;
//
//pTexture->GetDesc(&textureDesc);
//
//ptwTexture->SetTexture(textureDesc.Width, textureDesc.Height, pTexture, pShaderResource);
//
//m_TextureBuffer.insert(CTexturePair(hash, ptwTexture));
