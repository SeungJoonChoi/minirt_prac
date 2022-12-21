#include "minirt.h"

t_ray ray_set(t_vec *origin, t_vec* direction)
{
    t_ray ret;

    ret.orig = *origin;
    ret.dir = vec_unit(*direction);
    return (ret);
}

t_vec ray_at(t_ray *ray, double t) //정점좌표
{
    t_vec ret;

    ret.x = ray->orig.x + ray->dir.x * t;
    ret.y = ray->orig.y + ray->dir.y * t;
    ret.z = ray->orig.z + ray->dir.z * t;
    return (ret);
}

t_ray ray_viewport(t_camera *c, double u, double v)
{
    t_ray ret;
    ret.orig = c->orig;
    ret.dir.x = c->lower_left_corner.x + u * c->horizontal.x + v * c->vertical.x - c->orig.x;
    ret.dir.y = c->lower_left_corner.y + u * c->horizontal.y + v * c->vertical.y - c->orig.y;
    ret.dir.z = c->lower_left_corner.z + u * c->horizontal.z + v * c->vertical.z - c->orig.z;
    ret.dir = vec_unit(ret.dir);
    return (ret);
}