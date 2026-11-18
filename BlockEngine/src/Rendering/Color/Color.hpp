#pragma once

#include "../../Debugger/Logger/Logger.hpp"

struct Color
{
    float r = 1.0f;
    float g = 0.0f;
    float b = 1.0f;
    float a = 1.0f;

    Color() = default;

    Color(float R, float G, float B, float A)
    {
        if (R >= 0.0f && R <= 255.0f && G >= 0.0f && G <= 255.0f && B >= 0.0f && B <= 255.0f && A >= 0.0f && A <= 255.0f)
        {
            this->r = R / 255.0f;
            this->g = G / 255.0f;
            this->b = B / 255.0f;
            this->a = A / 255.0f;
        }
        else
        {
            r = 1.0f;
            g = 0.0f;
            b = 1.0f;
            a = 1.0f;
            error("Color value over 255 or under 0");
        }
    }
};
