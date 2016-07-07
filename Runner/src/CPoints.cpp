#include <CPoints.h>

#include <CCollectedPoint.h>

CPoints::CPoints()
{
}

CPoints::~CPoints()
{
}

void CPoints::Start()
{
}

void CPoints::Update()
{
    m_pEntity->m_Transform.RotateDegrees(0.0f, RotateSpeed * twTime->GetDeltaTime(), 0.0f);
}

void CPoints::End()
{
}

void CPoints::Collected()
{
    // disable current entity
    m_pEntity->GetDrawable()->SetActive(false);
    m_pEntity->RemovePhysicEntity();

    // create a new one
    auto entity = twActiveWorld->CreateEntity();
    entity->m_Transform.SetPosition(m_pEntity->m_Transform.GetPosition());

    auto mesh = twRenderer->CreateMeshDrawable();
    mesh->m_pMesh = twEngine.m_pResourceManager->GetMesh("ms_points");
    mesh->m_Material.SetMaterial(twEngine.m_pResourceManager->GetMaterial("PointExplosion"));
    mesh->m_DrawType = triebWerk::CMeshDrawable::EDrawType::DrawIndexed;
    mesh->m_Material.m_pGeometryShader.SetTexture(0, twResourceManager->GetTexture2D("t_noise"));
	mesh->m_D3DStates.m_pRasterizerState = twEngine.m_pGraphics->CreateRasterizerState(D3D11_CULL_NONE, D3D11_FILL_WIREFRAME);

    DirectX::XMFLOAT3 color = { 1.0f, 1.0f, 0.0f };
    int speed = 0;
    mesh->m_Material.m_ConstantBuffer.SetValueInBuffer(4, &color);
    mesh->m_Material.m_ConstantBuffer.SetValueInBuffer(5, &speed);

    entity->SetDrawable(mesh);
    entity->SetBehaviour(new CCollectedPoint());
    twActiveWorld->AddEntity(entity);
}
