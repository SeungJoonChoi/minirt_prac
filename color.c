#include "minirt.h"

t_color color_set(double r, double g, double b)
{
    t_color ret;

    ret.r = r;
    ret.g = g;
    ret.b = b;
    return (ret);
}

t_color ray_color(t_ray ray)
{
    t_color ret;
    t_vec unit_vec;
    double t;

    if (hit_sphere(vec(0, 0, 8), 3.0, ray))
        return (color_set(1.0, 0.0, 0.0));
    unit_vec = vec_unit(ray.dir);
    t = 0.5 * (unit_vec.y + 1.0);
    ret.r = 1.0 - (0.5 * t);
    ret.g = 1.0 - (0.3 * t);
    ret.b = 1.0;
    return (ret);
}