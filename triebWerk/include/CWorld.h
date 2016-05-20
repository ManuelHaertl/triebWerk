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

    private:
		static const size_t Start_Reserve_Size = 512;
        size_t m_CurrentSize;

        std::vector<CEntity*> m_Entities;
        std::vector<IBehaviour*> m_UpdateEntities;
        size_t m_EntitiesToUpdate;
        std::vector<CEntity*> m_DrawEntities;
        size_t m_EntitiesToDraw;
        std::vector<CEntity*> m_RemoveEntities;
        size_t m_EntitiesToRemove;

		CRenderer* m_pRenderingHandle;

        float m_TimePerFrame;
        float m_CurrentRenderTime;
        float m_PhysicTimeStamp;
        float m_CurrentPhysicTime;

    public:
        CWorld();
        ~CWorld();

    public:
        bool Initialize(CRenderer* a_pRenderer, const float a_TargetFPS, const float a_PhysicTimeStamp);
        bool Update(const float a_DeltaTime);
        void Shutdown();

        CEntity* CreateEntity() const;
        void AddEntity(CEntity* a_pEntity);
        void RemoveEntity(CEntity* a_pEntity);
        void ClearEntities();
        CEntity* GetEntity(size_t a_ID) const;
        size_t GetEntityCount() const;

    private:
        void GetEntityBehaviour();
        void GetEntityBehaviourAndDrawable();
        void UpdateEntityBehaviour();
        void UpdatePhysic();
        void LateUpdateEntityBehaviour();
        void RenderEntities();
        void DeleteRemoveEntities();

        void DeleteEntity(CEntity* a_pEntity);
    };
}