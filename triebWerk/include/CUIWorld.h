#pragma once
#include <CElementContainer.h>
#include <CFrameContainer.h>
#include <CUIEntity.h>
#include <CRenderer.h>

namespace triebWerk
{
    class CUIWorld
    {
    private:
        static const size_t Start_Reserve_Size = 2;
        size_t m_CurrentSize;

        CElementContainer<CEntity*> m_Entities;
        CFrameContainer<IBehaviour*> m_UpdateEntities;
        CFrameContainer<CEntity*> m_DrawEntities;

        CRenderer* m_pRenderingHandle;
    public:
        CUIWorld();
        ~CUIWorld();

        void Initialize(CRenderer* a_pRenderer);
        void Update();
        void Shutdown();

        CUIEntity* CreateUIEntity() const;
        void AddUIEntity(CUIEntity* a_pUIEntity);
        void RemoveUIEntity(CUIEntity* a_pUIEntity);
        void ClearUIEntities();
        CUIEntity* GetEntity(const size_t a_ID) const;
        size_t GetEntityCount() const;

    private:
        void DeleteEntity(CEntity* a_pEntity);
    };
}