#include <CRandom.h>

int triebWerk::CRandom::GetNumber(int a_Min, int a_Max)
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(a_Min, a_Max);

    return dist(mt);
}

float triebWerk::CRandom::GetNumber(float a_Min, float a_Max)
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<float> dist(a_Min, a_Max);

    return dist(mt);
}

triebWerk::CRandom::CRandom()
{
}

triebWerk::CRandom::~CRandom()
{
}
