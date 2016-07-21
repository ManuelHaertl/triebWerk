#pragma once
struct ETileType
{
    enum Type
    {
        ModelSize = -1,
        Nothing = 0,
        Air = 1,
        Checkpoint = 2,
        Points1 = 3,
        Shield = 4,
        Points2 = 5,
        Points3 = 6,
        Block1x1 = 17,
        Block2x2 = 18,
        Model05x05 = 33,
        Model05x05Flipped = 34,
        Model05x10 = 35,
        Model05x10Flipped = 36,
        Model05x20 = 37,
        Model05x20Flipped = 28,
        Model05x30 = 39,
        Model05x30Flipped = 40,
        Moving05x05Up = 41,
        Moving05x05Down = 42,
        Moving05x10Up = 43,
        Moving05x10UpFlipped = 44,
        Moving05x10Down = 45,
        Moving05x10DownFlipped = 46
    };
};
