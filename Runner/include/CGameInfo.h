#pragma once
class CGameInfo
{
public:
    int m_Difficulty;

public:
    CGameInfo();
    ~CGameInfo();

    static CGameInfo& Instance();
    void Reset();
};