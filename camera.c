#include "minirt.h"

t_camera camera(t_vec *orig, double fov, double aspect_ratio)
{
    t_camera ret;
    double theta;
    double h;

    theta = degToRad(fov);
    h = tan(theta/2);
    ret.viewport_height = 2.0 * h;
    ret.viewport_width = aspect_ratio * ret.viewport_height;

    ret.orig = *orig;
    ret.focal_length = 1.0;
    return (ret);
}