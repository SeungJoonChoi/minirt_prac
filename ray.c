#include "minirt.h"

t_ray ray_set(t_vec *origin, t_vec* direction)
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

t_ray ray_viewport(t_camera *camera, double u, double v)
{
    t_ray ret;
    ret.orig = camera->orig;
    ret.dir = vec(camera->lower_left_corner.x + u*camera->horizontal.x + v*camera->vertical.x - camera->orig.x);
    //

    return (ret);
}