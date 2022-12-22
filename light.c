#include "minirt.h"

/*
ambient lighting
*/

t_light *light_point(t_vec orig, t_color color, double ratio)
{
    t_light *new;

    new = (t_light*)malloc(sizeof(t_light));
    new->orig = orig;
    new->color = color;
    new->ratio = ratio;
    return (new);
}

t_color phong_lighting(t_scene *scene)
{
    t_color light_color;
    // t_obj *light;

    light_color = color(0, 0, 0);
    // light = scene->light.next;
    light_color = vec_sum(light_color, scene->ambient);
    return (vec_limit(vec_mul_v(light_color, scene->rec.albedo), color(1, 1, 1)));
}