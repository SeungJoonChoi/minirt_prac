#include "minirt.h"

t_image image(int width, double aspect_ratio)
{
    t_image ret;

    ret.aspect_ratio = aspect_ratio;
    ret.image_width = width;
    ret.image_height = (int)((double)width / aspect_ratio);
    return (ret);
}