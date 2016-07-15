#include <CRenderBatch.h>

triebWerk::CRenderBatch::CRenderBatch() :
	m_pOpaqueMeshBuffer(nullptr),
	m_pTransparentMeshBuffer(nullptr),
	m_pInstancedMeshBuffer(nullptr),
	m_pFontBuffer(nullptr),
	m_OpaqueMeshCounter(0),
	m_TransparentMeshCounter(0),
	m_InstancedMeshBatchCount(0),
	m_FontCommandCount(0),
	m_UIElementCount(0)
{

}

triebWerk::CRenderBatch::~CRenderBatch()
{
}

void triebWerk::CRenderBatch::Create(CGraphics * a_pGraphics)
{
	//Initialize rendercommands buffer
	m_pTransparentMeshBuffer = new CMeshDrawable*[m_MaxDrawables];
	m_pOpaqueMeshBuffer = new CMeshDrawable*[m_MaxDrawables];
	m_pInstancedMeshBuffer = new CInstancedMeshBatch[m_MaxInstancedMeshBatch];
	m_pFontBuffer = new CFontDrawable*[m_MaxFonts];
	m_pUIBuffer = new CUIDrawable*[m_MaxUIElements];

	//Initialize the InstancedBatches for later use
	for (size_t i = 0; i < m_MaxInstancedMeshBatch; i++)
	{
		m_pInstancedMeshBuffer[i].Initialize(a_pGraphics);
	}
}

void triebWerk::CRenderBatch::Free()
{
	if(m_pOpaqueMeshBuffer != nullptr)
		delete[] m_pOpaqueMeshBuffer;
	if (m_pTransparentMeshBuffer != nullptr)
		delete[] m_pTransparentMeshBuffer;
	if (m_pInstancedMeshBuffer != nullptr)
		delete[] m_pInstancedMeshBuffer;
	if (m_pFontBuffer != nullptr)
		delete[] m_pFontBuffer;
	if (m_pUIBuffer != nullptr)
		delete[] m_pUIBuffer;
}

void triebWerk::CRenderBatch::Reset()
{
	//Reset all buffers
	m_OpaqueMeshCounter = 0;
	m_TransparentMeshCounter = 0;
	m_InstancedMeshBatchCount = 0;
	m_FontCommandCount = 0;
	m_UIElementCount = 0;
}
