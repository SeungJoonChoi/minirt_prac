#include "minirt.h"

/*
ambient lighting
*/

t_light *point_light(t_vec orig, t_color color, double ratio)
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
    t_obj *light;

    light_color = color(0, 0, 0);
    light = scene->light.next;
    while (light)
    {
        light_color = vec_sum(light_color, point_light_get(scene, light->element));
        light = light->next;
    }
    light_color = vec_sum(light_color, scene->ambient);
    return (vec_limit(vec_mul_v(light_color, scene->rec.albedo), color(1, 1, 1)));
}

t_color point_light_get(t_scene *scene, t_light *light)
{
    t_color diffuse;
    t_vec light_dir;
    double ratio;

    /*
    diffuse light
    '광원을 향한 벡터'과 '충돌점의 법선벡터'의 사이각를 이용해
    마주보고 있을수록 받는 빛의 양을 늘려줌.
    */
    light_dir = vec_unit(vec_sub(light->orig, scene->rec.p));
    ratio = vec_dot(light_dir, scene->rec.normal); //단위벡터끼리 내적하면 0.0 ~ 1.0 사이의 값
    //내적을 이용하여 코사인0도에 가까울수록 서로 마주봄
    //90도를 넘어가면 음수이므로 빛의 영향을 전혀 받지 않음.
    if (ratio < 0.0)
        ratio = 0.0;
    diffuse = vec_mul(light->color, ratio);
    return (diffuse);
}