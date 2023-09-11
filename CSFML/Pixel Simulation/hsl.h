#pragma once
#ifndef HSL_COLOR
#define HSL_COLOR

#include "SFML/Graphics/Color.h"
#include <algorithm>
#include <cmath>

struct HSL
{
public:

    double Hue;
    double Saturation;
    double Luminance;

    HSL();
    HSL(int H, int S, int L);

    sfColor TurnToRGB();

private:

    double HueToRGB(double arg1, double arg2, double H);

};

HSL TurnToHSL(const sfColor& C);

#endif // HSL_COLOR