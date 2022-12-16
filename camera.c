#include "minirt.h"

t_vec lower_left_corner(t_camera *camera)
{
    t_vec ret;

    ret.x = camera->orig.x - (camera->horizontal.x / 2.0) - (camera->vertical.x / 2.0) - 0;
    ret.y = camera->orig.y - (camera->horizontal.y / 2.0) - (camera->vertical.y / 2.0) - 0;
    ret.z = camera->orig.z - (camera->horizontal.z / 2.0) - (camera->vertical.z / 2.0) - camera->focal_length;
    return (ret);
}

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

    ret.horizontal = vec(ret.viewport_width, 0, 0);
    ret.vertical = vec(0, ret.viewport_height, 0);

    ret.lower_left_corner = lower_left_corner(&ret);
    return (ret);
}