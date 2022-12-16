#include "minirt.h"

t_ray ray(t_vec *origin, t_vec* direction)
{
    t_ray ret;

    ret.orig = *origin;
    ret.dir = *direction;
    return (ret);
}

t_vec ray_at(t_ray *ray, double t)
{
    t_vec ret;

    ret.x = ray->orig.x + ray->dir.x * t;
    ret.y = ray->orig.y + ray->dir.y * t;
    ret.z = ray->orig.z + ray->dir.z * t;
    return (ret);
}