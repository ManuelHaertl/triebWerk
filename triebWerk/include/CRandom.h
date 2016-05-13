#pragma once
#include <random>

namespace triebWerk
{
    class CRandom
    {
    public:
        static int GetNumber(int a_Min, int a_Max);
        static float GetNumber(float a_Min, float a_Max);

    private:
        CRandom();
        ~CRandom();
    };
}