#include "minirt.h"

int rgb_to_int(double trans, t_color *color)
{
    int t;
    int r;
    int g;
    int b;

    t = trans * 255.999;
    r = color->r * 255.999;
    g = color->g * 255.999;
    b = color->b * 255.999;
    return (t << 24 | r << 16 | g << 8 | b);
}