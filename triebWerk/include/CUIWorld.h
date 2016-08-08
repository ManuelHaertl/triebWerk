#pragma once
#include <CElementContainer.h>
#include <CFrameContainer.h>
#include <CUIEntity.h>
#include <CRenderer.h>

namespace triebWerk
{
    class CUIWorld
    {
    public:
        enum class EScreenMatchState
        {
            Width,
            Height
        };

    private:
        static const size_t Start_Reserve_Size = 2;
        static float m_ScreenResolutionX;
        static float m_ScreenResolutionY;
        size_t m_CurrentSize;

        CElementContainer<CUIEntity*> m_Entities;
        CFrameContainer<IBehaviour*> m_UpdateEntities;
        CFrameContainer<CUIEntity*> m_DrawEntities;
        CFrameContainer<CUIEntity*> m_RemoveEntities;

        CRenderer* m_pRenderingHandle;

        float m_ReferenceResolutionX;
        float m_ReferenceResolutionY;

        EScreenMatchState m_ScreenMatchState;

    public:
        CUIWorld();
        ~CUIWorld();

        void Initialize(CRenderer* a_pRenderer);
        void Update();
        void Shutdown();
        void RemoveDeleteEntities();

        void SetScreenResolution(const int m_Width, const int m_Height);
        void SetReferenceResolution(const float m_Width, const float m_Height, const EScreenMatchState m_MatchState);

        CUIEntity* CreateUIEntity() const;
        void AddUIEntity(CUIEntity* a_pUIEntity);
        void RemoveUIEntity(CUIEntity* a_pUIEntity);
        void ClearUIEntities();
        CUIEntity* GetEntity(const size_t a_ID) const;
        size_t GetEntityCount() const;

    private:
        void DeleteEntity(CUIEntity* a_pUIEntity);
        void UpdateScreenInformation();
    };
}