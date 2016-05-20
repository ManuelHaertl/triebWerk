#include <CInstancedMeshBatch.h>

triebWerk::CInstancedMeshBatch::CInstancedMeshBatch() :
	m_pMaterialDeterminer(0),
	m_pMeshDeterminer(nullptr),
	m_InstanceCount(0),
	m_pInstanceBuffer(nullptr),
	m_pInstanceDataBuffer(nullptr),
	m_pGraphicsHandle(nullptr)
{
}

triebWerk::CInstancedMeshBatch::~CInstancedMeshBatch()
{
	delete[] m_pInstanceBuffer;
}

void triebWerk::CInstancedMeshBatch::Initialize(CGraphics * a_pGraphicsHandle)
{
	m_pInstanceDataBuffer = new SDataPerInstance[MAX_INSTANCE_COUNT];
	m_InstanceCount = 0;
	m_pGraphicsHandle = a_pGraphicsHandle;
}

void triebWerk::CInstancedMeshBatch::AddDrawable(CMeshDrawable * a_pDrawable)
{
	if (m_InstanceCount <= MAX_INSTANCE_COUNT)
	{
		m_pInstanceDataBuffer[m_InstanceCount].Transformation = a_pDrawable->m_Transformation;
	}
}

void triebWerk::CInstancedMeshBatch::Reset()
{
	m_InstanceCount;
}
