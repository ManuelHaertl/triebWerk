#pragma once
#include <CMeshDrawable.h>
#include <CID.h>
#include <CGraphics.h>

#define MAX_INSTANCE_COUNT 8000

namespace triebWerk
{

	class CInstancedMeshBatch
	{
	public:
		struct SDataPerInstance
		{
			DirectX::XMMATRIX Transformation;
		};

	public:
		size_t m_pMaterialDeterminer;
		CMesh* m_pMeshDeterminer;

	private:
		size_t m_InstanceCount;
		ID3D11Buffer* m_pInstanceBuffer;
		SDataPerInstance* m_pInstanceDataBuffer;
		CGraphics* m_pGraphicsHandle;

	public:
		CInstancedMeshBatch();
		~CInstancedMeshBatch();

	public:
		void Initialize(CGraphics* a_pGraphicsHandle);
		void AddDrawable(CMeshDrawable* a_pDrawable);
		void Reset();

	};
}