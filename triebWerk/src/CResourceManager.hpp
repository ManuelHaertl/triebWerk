#pragma once
#include <CResourceManager.h>

template<typename T>void triebWerk::CResourceManager::GetAll(const char* a_pPath, std::vector<T*>* a_pOutData)
{

//This variable exists only so it can be decltyped to compare with T
#pragma warning( push )
#pragma warning( disable : 4101)
T* typeVar;
#pragma warning( pop ) 


	std::vector<SFile>files = SearchFolderForAllFiles(a_pPath);

	for (size_t i = 0; i < files.size(); i++)
	{
		switch (files[i].FileType)
		{
		case triebWerk::EFileType::PNG:
		{
			CTexture2D* texture = GetTexture2D(files[i].FileName.c_str());

			if (texture != nullptr)
			{
				if (std::is_same<decltype(texture), decltype(typeVar)>::value)
				{
					a_pOutData->push_back((T*)texture);
				}
			}
		}break;
		case triebWerk::EFileType::OBJ:
		{
			CMesh* mesh = GetMesh(files[i].FileName.c_str());

			if (mesh != nullptr)
			{
				if (std::is_same<decltype(mesh), decltype(typeVar)>::value)
				{
					a_pOutData->push_back((T*)mesh);
				}
			}
		}break;
		case triebWerk::EFileType::MP3:
		{
			//a_pOutData->push_back(GetMesh(files[i].FileName));
		}break;
		case triebWerk::EFileType::TMX:
		{
			CTilesetMap* tileset = GetTileset(files[i].FileName.c_str());

			if (tileset != nullptr)
			{
				if (std::is_same<decltype(tileset), decltype(typeVar)>::value)
				{
					a_pOutData->push_back((T*)tileset);
				}
			}
		}break;
		case triebWerk::EFileType::HLSL:
		{
			CMaterial* material = GetMaterial(files[i].FileName.c_str());

			if (material != nullptr)
			{
				if (std::is_same<decltype(material), decltype(typeVar)>::value)
				{
					a_pOutData->push_back((T*)material);
				}
			}
		}break;
		case triebWerk::EFileType::TWF:
		{
			CTWFData* twfData = GetTWFData(files[i].FileName.c_str());

			if (twfData != nullptr)
			{
				if (std::is_same<decltype(twfData), decltype(typeVar)>::value)
				{
					a_pOutData->push_back((T*)twfData);
				}
			}
		}break;
		case triebWerk::EFileType::NONE:
			break;
		}
	}

	//Iterate over all possible files
	//for (size_t i = 0; i < files.size(); i++)
	//{
	//	if (files[i].FileType == a_FileType)
	//	{
	//		switch (a_FileType)
	//		{
	//		case triebWerk::EFileType::PNG:
	//		{
	//			T* data = (T*)GetTexture2D(files[i].FileName.c_str());
	//			if (data != nullptr)
	//				a_pOutData->push_back(data);
	//		}break;
	//		case triebWerk::EFileType::OBJ:
	//		{
	//			T* data = (T*)GetMesh(files[i].FileName.c_str());
	//			if (data != nullptr)
	//				a_pOutData->push_back(data);
	//		}break;
	//		case triebWerk::EFileType::MP3:
	//		{
	//			//a_pOutData->push_back(GetMesh(files[i].FileName));
	//		}break;
	//		case triebWerk::EFileType::TMX:
	//		{
	//			T* data = (T*)GetTileset(files[i].FileName.c_str());
	//			if (data != nullptr)
	//				a_pOutData->push_back(data);
	//		}break;
	//		case triebWerk::EFileType::HLSL:
	//		{
	//			T* data = (T*)GetMaterial(files[i].FileName.c_str());
	//			if (data != nullptr)
	//				a_pOutData->push_back(data);
	//		}break;
	//		case triebWerk::EFileType::TWF:
	//		{
	//			T* data = (T*)GetTWFData(files[i].FileName.c_str());
	//			if (data != nullptr)
	//				a_pOutData->push_back(data);
	//		}break;
	//		case triebWerk::EFileType::NONE:
	//			break;
	//		}
	//	}
	//}
}