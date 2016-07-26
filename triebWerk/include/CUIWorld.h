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

        CElementContainer<CUIEntity*> m_Entities;
        CFrameContainer<IBehaviour*> m_UpdateEntities;
        CFrameContainer<CUIEntity*> m_DrawEntities;
        CFrameContainer<CUIEntity*> m_RemoveEntities;

        CRenderer* m_pRenderingHandle;
        float m_ReferenceResolutionX;
        float m_ReferenceResolutionY;

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