#include "minirt.h"

t_vec lower_left_corner(t_camera *camera)
{
    t_vec ret;

    ret.x = camera->orig.x - (camera->viewport_width / 2.0);
    ret.y = camera->orig.y - (camera->viewport_height / 2.0);
    ret.z = camera->orig.z - camera->focal_length;
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

    ret.lower_left_corner = lower_left_corner(&ret);
    return (ret);
}