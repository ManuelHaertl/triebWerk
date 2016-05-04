#pragma once
struct ETileType
{
    enum Type
    {
        Invalid = -1,
        Nothing = 0,
        Air = 1,
        Checkpoint = 2,
        Points = 3,
        Shield = 4,
        Block1x1 = 17,
        Block2x2 = 18
    };
};
