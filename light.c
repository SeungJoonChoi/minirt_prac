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