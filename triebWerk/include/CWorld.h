#pragma once
#include <vector>

#include <CEntity.h>
#include <CPhysicWorld.h>
#include <CRenderer.h>

namespace triebWerk
{
    class CWorld
    {
    public:
        CPhysicWorld* m_pPhysicWorld;

    public:
		static const size_t Start_Reserve_Size = 512;
        size_t m_CurrentSize;

        std::vector<CEntity*> m_Entities;

		CRenderer* m_pRenderingHandle;

    public:
        CWorld();
        ~CWorld();

    public:
        bool Initialize(CRenderer* a_pRenderer);
        bool Update(const float a_DeltaTime);
        void Shutdown();

        CEntity* CreateEntity() const;
        void AddEntity(CEntity* a_pEntity);
        void RemoveEntity(CEntity* a_pEntity);
        void ClearEntities();

    private:
        void DeleteEntity(CEntity* a_pEntity);
    };
}