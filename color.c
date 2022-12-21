#include "minirt.h"

t_color color(double r, double g, double b)
{
    t_color ret;

    ret.r = r;
    ret.g = g;
    ret.b = b;
    return (ret);
}

t_color ray_color(t_ray ray)
{
    t_vec unit_vec;
    double t;
    double r;

    r = hit_sphere(vec(-3, 3, 5), 2, ray);
    if (r > 0.0)
    {
        unit_vec = ray_at(&ray, r);
        unit_vec = vec_unit(vec(unit_vec.x + 3, unit_vec.y - 3, unit_vec.z + 5));
        return (color((1.0 + unit_vec.x) * 0.5, (1.0 + unit_vec.y) * 0.5, (1.0 + unit_vec.z) * 0.5));
    }
    // if (hit_sphere(vec(0, 0, 8), 3.0, ray))
    //     return (color(1.0, 0.0, 0.0));
    unit_vec = vec_unit(ray.dir);
    t = 0.5 * (unit_vec.y + 1.0);
    return (color(1.0 - (0.5 * t), 1.0 - (0.3 * t), 1.0));
}