#pragma once
#include <CEntity.h>
#include <vector>

namespace triebWerk
{
    class CWorld
    {
    private:
        static const size_t Start_Reserve_Size = 512;
        size_t m_CurrentSize;

        std::vector<CEntity*> m_Entities;

        std::vector<IBehaviour*> m_UpdateEntities;
        size_t m_UpdateEntityCount;

    public:
        CWorld();
        ~CWorld();

    public:
        bool Initialize();
        bool Update();
        void Shutdown();

        void AddEntity(CEntity* a_pEntity);
        void RemoveEntity(CEntity* a_pEntity);
        void ClearEntities();

    private:
        void DeleteEntity(CEntity* a_pEntity);
    };
}