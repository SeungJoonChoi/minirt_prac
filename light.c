#include "minirt.h"

/*
ambient lighting
*/

t_light *point_light(t_vec orig, t_color color, double intensity)
{
    t_light *new;

    new = (t_light*)malloc(sizeof(t_light));
    new->orig = orig;
    new->color = color;
    new->intensity = intensity;
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

t_vec reflect(t_vec light_dir, t_vec normal)
{
    t_vec ret;
    t_vec a;
    double n;

    n = vec_dot(light_dir, normal);
    a = vec_mul(normal, n);
    ret = vec_sum(vec_sum(vec_mul(light_dir, -1), a), a);
    return (ret);
}

t_color point_light_get(t_scene *scene, t_light *light)
{
    t_vec light_dir;
    //diffuse
    t_color diffuse;
    double kd;
    //specular
    t_vec specular;
    t_vec reflect_dir;
    double spec;
    double ksn; // shininess value of object
    double ks;  // specular strength

    light_dir = vec_unit(vec_sub(light->orig, scene->rec.p));

    /*
    diffuse light
    '광원을 향한 벡터'과 '충돌점의 법선벡터'의 사이각를 이용해
    마주보고 있을수록 받는 빛의 양을 늘려줌.
    */
    kd = vec_dot(light_dir, scene->rec.normal); //단위벡터끼리 내적하면 0.0 ~ 1.0 사이의 값
    //내적을 이용하여 코사인0도에 가까울수록 서로 마주봄
    //90도를 넘어가면 음수이므로 빛의 영향을 전혀 받지 않음.
    if (kd < 0.0)
        kd = 0.0;
    diffuse = vec_mul(light->color, kd);

    /*
    specular light
    */
    reflect_dir = reflect(light_dir, scene->rec.normal);
    reflect_dir = vec_mul(reflect_dir, -1);
    spec = vec_dot(reflect_dir, scene->ray.dir);
    if (spec < 0.0)
        spec = 0.0;
    ksn = SHININESS;
    ks = SPECULAR_INTENSITY;
    spec = pow(spec, ksn);
    specular = vec_mul(vec_mul(light->color, ks), spec);
    return (vec_sum(diffuse, specular));

    (void)specular;
    return (diffuse);
}