#include <CPlayer.h>

CPlayer::CPlayer() :
    m_Rotation(0.0f)
{
}

CPlayer::~CPlayer()
{
}

void CPlayer::Start()
{
    triebWerk::CMeshDrawable* mesh = new triebWerk::CMeshDrawable();
    mesh->m_pMesh = twEngine.m_pResourceManager->GetMesh("cube.obj");
    mesh->m_Material.m_ConstantBuffer.InitializeConstantBufffer(twEngine.m_pGraphics->GetDevice());
    m_pEntity->SetDrawable(mesh);

    m_pEntity->SetPhysicEntity(twPhysic->CreatePhysicEntity());
    auto collbox = twPhysic->CreateOBBCollider();
    collbox->CreateFromVertices(mesh->m_pMesh->m_pVertices, mesh->m_pMesh->m_VertexCount);
    collbox->m_CheckCollision = true;
    m_pEntity->GetPhysicEntity()->AddCollider(collbox);

    m_pEntity->m_Transform.SetPosition(0.0f, -6.0f, 0.0f);
    m_pEntity->m_Transform.SetScale(10.0f, 1.0f, 1.0f);

}

void CPlayer::Update()
{
    m_Rotation += twTime->GetDeltaTime() * 20.0f;
    m_pEntity->m_Transform.SetRotationDegrees(0.0f, 0.0f, m_Rotation);

    std::cout << twTime->GetDeltaTime() << std::endl;

    if (twKeyboard.IsState(triebWerk::EKey::D1, triebWerk::EButtonState::Down))
    {
        auto entity = twWorld->CreateEntity();
        triebWerk::CMeshDrawable* mesh = new triebWerk::CMeshDrawable();
        mesh->m_pMesh = twEngine.m_pResourceManager->GetMesh("cube.obj");
        mesh->m_Material.m_ConstantBuffer.InitializeConstantBufffer(twEngine.m_pGraphics->GetDevice());
        entity->SetDrawable(mesh);

        entity->SetPhysicEntity(twPhysic->CreatePhysicEntity());
        entity->GetPhysicEntity()->SetBody(twPhysic->CreateBody());
        auto collider = twPhysic->CreateSphereCollider();
        collider->CreateFromVertices(mesh->m_pMesh->m_pVertices, mesh->m_pMesh->m_VertexCount);
        collider->m_CheckCollision = false;
        entity->GetPhysicEntity()->AddCollider(collider);

        entity->m_Transform.SetPosition(0.0f, 5.0f, 0.0f);
        entity->m_Transform.SetScale(1.0f, 1.0f, 1.0f);
        twWorld->AddEntity(entity);
    }

    if (twKeyboard.IsState(triebWerk::EKey::D2, triebWerk::EButtonState::Down))
    {
        auto entity = twWorld->CreateEntity();
        triebWerk::CMeshDrawable* mesh = new triebWerk::CMeshDrawable();
        mesh->m_pMesh = twEngine.m_pResourceManager->GetMesh("cube.obj");
        mesh->m_Material.m_ConstantBuffer.InitializeConstantBufffer(twEngine.m_pGraphics->GetDevice());
        entity->SetDrawable(mesh);

        entity->SetPhysicEntity(twPhysic->CreatePhysicEntity());
        entity->GetPhysicEntity()->SetBody(twPhysic->CreateBody());
        auto collider = twPhysic->CreateAABBCollider();
        collider->CreateFromVertices(mesh->m_pMesh->m_pVertices, mesh->m_pMesh->m_VertexCount);
        collider->m_CheckCollision = false;
        entity->GetPhysicEntity()->AddCollider(collider);

        entity->m_Transform.SetScale(1.0f, 1.0f, 1.0f);
        entity->m_Transform.SetPosition(0.0f, 5.0f, 0.0f);
        twWorld->AddEntity(entity);
    }

    if (twKeyboard.IsState(triebWerk::EKey::D3, triebWerk::EButtonState::Down))
    {
        auto entity = twWorld->CreateEntity();
        triebWerk::CMeshDrawable* mesh = new triebWerk::CMeshDrawable();
        mesh->m_pMesh = twEngine.m_pResourceManager->GetMesh("cube.obj");
        mesh->m_Material.m_ConstantBuffer.InitializeConstantBufffer(twEngine.m_pGraphics->GetDevice());
        entity->SetDrawable(mesh);

        entity->SetPhysicEntity(twPhysic->CreatePhysicEntity());
        entity->GetPhysicEntity()->SetBody(twPhysic->CreateBody());
        auto collider = twPhysic->CreateOBBCollider();
        collider->CreateFromVertices(mesh->m_pMesh->m_pVertices, mesh->m_pMesh->m_VertexCount);
        collider->m_CheckCollision = false;
        entity->GetPhysicEntity()->AddCollider(collider);

        entity->m_Transform.SetPosition(0.0f, 5.0f, 0.0f);
        entity->m_Transform.SetScale(3.0f, 1.0f, 1.0f);
        entity->m_Transform.SetRotationDegrees(0.0f, 0.0f, 45.0f);
        twWorld->AddEntity(entity);
    }
}

void CPlayer::CollisionEnter(triebWerk::CCollisionEvent a_Collision)
{
    std::cout << "Enter with: " << a_Collision.m_pPartner << std::endl;
    twWorld->RemoveEntity(a_Collision.m_pPartner);
}
