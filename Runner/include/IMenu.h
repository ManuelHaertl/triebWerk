#pragma once
#include <SUIInput.h>
class IMenu
{
public:
    IMenu();
    virtual ~IMenu();

    virtual void Start() = 0;
    virtual void Update(const SUIInput& m_rInput) = 0;
    virtual void End() = 0;
    virtual void Resume() = 0;
};