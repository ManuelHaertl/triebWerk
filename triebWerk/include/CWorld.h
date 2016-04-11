#pragma once
#include <vector>

#include <CEntity.h>
#include <CPhysicWorld.h>

namespace triebWerk
{
    class CWorld
    {
    public:
        CPhysicWorld* m_pPhysicWorld;

    private:
        static const size_t Start_Reserve_Size = 512;
        size_t m_CurrentSize;

        std::vector<CEntity*> m_Entities;

    public:
        CWorld();
        ~CWorld();

    public:
        bool Initialize();
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