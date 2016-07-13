#pragma once
#include <CMeshDrawable.h>
#include <CID.h>
#include <CCamera.h>
#include <CGraphics.h>

#define MAX_INSTANCE_COUNT 8000
#define MAX_DATA_PER_INSTANCE 120

namespace triebWerk
{

	class CInstancedMeshBatch
	{
	public:
		//This structure defines the batch 
		struct SMeshIdentifier
		{
			//Material Hash
			size_t m_pMaterialDeterminer;
			//Mesh pointer
			CMesh* m_pMeshDeterminer;
			//Constant Buffer
			char* m_pConstantBuffer;
		};

	public:
		CMeshDrawable* DEBUG_pDrawable;
		CMaterial* m_pMaterial;
		SMeshIdentifier m_Identifier;
		size_t m_InstanceCount;
		size_t m_SizeOfDataPerInstance;

	private:
		ID3D11Buffer* m_pInstanceBuffer;
		char* m_pInstanceDataBuffer;
		CGraphics* m_pGraphicsHandle;

	public:
		CInstancedMeshBatch();
		~CInstancedMeshBatch();

	public:
		void Initialize(CGraphics* a_pGraphicsHandle);
		//void Draw(CCamera* a_pCamera);
		void SetBuffers();
		void AddDrawable(CMeshDrawable* a_pDrawable);
		void Reset();

	};
}