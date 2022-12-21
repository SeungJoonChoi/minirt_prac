#include "minirt.h"

/*
구의 방정식 x^2 + y^2 + z^2 = r^2
-> (x - C.x)^2 + (y - C.y)^2 + (z - C.z)^2 = r^2 (C는 구의 중심)
-> (P - C) * (P - C) = r^2 (P는 구위의 임의의 좌표)
-> |(P - C)|^2 = r^2
직선의 방정식 A + t*b (A원점 b방향벡터)
-> |(A + tb - C)|^2 = r^2
-> (b*b)t^2 + 2b*(A-C)t + (A-C)*(A-C) - r^2 = 0
짝수판별식 (b/2)^2 -ac
b가 단위벡터라고 가정하면
a = 1
b/2 = b*(A-C)
c = (A-C)*(A-C) - r^2
판별식이 양수일때만 픽셀의 색을 구해옴

!! b를 단위벡터라고 가정하고 쓰려면 ray.dir을 모두 단위벡터로 초기화 해야함
*/

// int hit_sphere(t_vec center, double radius, t_ray ray)
// {
//     t_vec oc;
//     t_vec unit_ray;
//     double b;
//     double c;
//     double discriminant;

//     oc = vec_sub(ray.orig, center);
//     unit_ray = vec_unit(ray.dir);
//     b = vec_dot(unit_ray, oc);
//     c = vec_dot(oc, oc) - (radius * radius);
//     discriminant = b * b - c;
//     if (discriminant >= 0)
//         return (1);
//     return (0);
// }

// double hit_sphere(t_vec center, double radius, t_ray ray)
// {
//     t_vec oc;
//     double half_b;
//     double c;
//     double discriminant;

//     oc = vec_sub(ray.orig, center);
//     half_b = vec_dot(ray.dir, oc);
//     c = length_squared(oc) - (radius * radius);
//     discriminant = (half_b * half_b) - c;
//     if (discriminant < 0)
//         return (0);
//     else
//         return (-half_b - sqrt(discriminant));
// }

void set_face_normal(t_ray *ray, t_hit_record *rec)
{
    rec->front_face = vec_dot(ray->dir, rec->normal) < 0;
    if (!rec->front_face)
        rec->normal = vec_mul(rec->normal, -1.0);
}

int hit_sphere(t_ray *ray, t_sphere *sphere, t_hit_record *out)
{
    t_vec oc;
    double half_b;
    double c;
    double discriminant;
    double sqrtd;
    double root;

    oc = vec_sub(ray->orig, sphere->orig);
    half_b = vec_dot(ray->dir, oc);
    c = length_squared(oc) - (sphere->rad * sphere->rad);
    discriminant = (half_b * half_b) - c;
    if (discriminant < 0)
        return (0);
    else
    {
        sqrtd = sqrt(discriminant);
        root = -half_b - sqrtd;
        if (root < out->t_min || root > out->t_max)
        {
            root = -half_b + sqrtd;
            if (root < out->t_min || root > out->t_max)
                return (0);
        }
        out->t = root;
        out->t_max = out->t;
        out->p = ray_at(ray, root);
        out->normal = vec_div(vec_sub(out->p, sphere->orig), sphere->rad);

        set_face_normal(ray, out);
    }
    return (1);
}