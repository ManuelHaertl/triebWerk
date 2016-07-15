#pragma once
#include <CElementContainer.h>
#include <CFrameContainer.h>
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
		static const size_t Start_Reserve_Size = 2;
        size_t m_CurrentSize;

        CElementContainer<CEntity*> m_Entities;
        CFrameContainer<IBehaviour*> m_UpdateEntities;
        CFrameContainer<CEntity*> m_DrawEntities;
        CFrameContainer<CEntity*> m_RemoveEntities;

		CRenderer* m_pRenderingHandle;
        float m_PhysicTimeStamp;

    public:
        CWorld();
        ~CWorld();

    public:
        void Initialize(CRenderer* a_pRenderer, const float a_PhysicTimeStamp);
        void Update(const bool a_Render, const bool a_UpdatePhysic);
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