#include <CWorld.h>

triebWerk::CWorld::CWorld() :
    m_pPhysicWorld(nullptr),
    m_CurrentSize(Start_Reserve_Size)
{
}

triebWerk::CWorld::~CWorld()
{
}

bool triebWerk::CWorld::Initialize(CRenderer* a_pRenderer)
{
    m_pPhysicWorld = new CPhysicWorld();

    // reserve some spots so the vector doesn't need
    // to get resized too often during runtime
    m_Entities.reserve(Start_Reserve_Size);

	m_pRenderingHandle = a_pRenderer;

    return true;
}

bool triebWerk::CWorld::Update(const float a_DeltaTime)
{
    // check what behaviour the entity has
    for (size_t i = 0; i < m_Entities.size(); ++i)
    {
        if (m_Entities[i]->GetBehaviour() != nullptr)
        {
            m_Entities[i]->GetBehaviour()->Update();
        }

		//Temp Debug drawing
		if (m_Entities[i]->GetDrawable() != nullptr)
		{
			//Queue up rendercommand 
			m_pRenderingHandle->AddRenderCommand(m_Entities[i]->GetDrawable()->GetRenderCommand());
		}
    }



    m_pPhysicWorld->Update(a_DeltaTime);
    return true;
}

void triebWerk::CWorld::Shutdown()
{
    ClearEntities();

    if (m_pPhysicWorld != nullptr)
        delete m_pPhysicWorld;
}

triebWerk::CEntity* triebWerk::CWorld::CreateEntity() const
{
    CEntity* entity = new CEntity();
    return entity;
}

void triebWerk::CWorld::AddEntity(CEntity* a_pEntity)
{
    // resize if the vector doesn't have any more reserved spots
    if (m_Entities.size() >= m_CurrentSize)
    {
        m_CurrentSize *= 2;
        m_Entities.reserve(m_CurrentSize);
    }

    if (a_pEntity->GetBehaviour() != nullptr)
    {
        a_pEntity->GetBehaviour()->Start();
    }

    // check for Physic Entity
    if (a_pEntity->GetPhysicEntity() != nullptr)
    {
        m_pPhysicWorld->AddPhysicEntity(a_pEntity->GetPhysicEntity());
    }

    a_pEntity->SetInWorldState(true);
    m_Entities.push_back(a_pEntity);
}

void triebWerk::CWorld::RemoveEntity(CEntity* a_pEntity)
{
    for (size_t i = 0; i < m_Entities.size(); ++i)
    {
        if (m_Entities[i] == a_pEntity)
        {
            DeleteEntity(a_pEntity);
            m_Entities.erase(m_Entities.begin() + i);
            break;
        }
    }
}

void triebWerk::CWorld::ClearEntities()
{
    for (size_t i = 0; i < m_Entities.size(); ++i)
    {
        DeleteEntity(m_Entities[i]);
    }

    m_Entities.clear();
}

void triebWerk::CWorld::DeleteEntity(CEntity * a_pEntity)
{
	a_pEntity->RemoveBehaviour();

	a_pEntity->RemovePhysicEntity();

	a_pEntity->RemoveDrawable();

    delete a_pEntity;
}
