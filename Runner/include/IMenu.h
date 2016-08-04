#pragma once
#include <SUIInput.h>
#include <EMenus.h>

class IMenu
{
protected:
    bool m_ShallExit = false;

public:
    IMenu();
    virtual ~IMenu();

    virtual void Start();
    virtual void Update(const SUIInput& m_rInput);
    virtual void End();
    virtual void Resume();
    virtual void Entered();
    virtual bool Exited();
};