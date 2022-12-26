#include "minirt.h"

t_cylinder *cylinder(t_vec origin, t_vec dir, double diameter, double height, t_color albedo)
{
    t_cylinder *new;

    new = (t_cylinder*)malloc(sizeof(t_cylinder));
    new->orig = origin;
    new->dir = vec_unit(dir);
    new->rad = diameter * 0.5;
    new->half_h = height * 0.5;
    new->albedo = albedo;
    return (new);
}

int hit_cylinder(t_ray *ray, t_cylinder *cylinder, t_hit_record *rec)
{
    t_vec oc;
    double a;
    double half_b;
    double c;
    double discriminant;
    double sqrtd;
    double root;
    double h;
    t_vec f;

    oc = vec_sub(ray->orig, cylinder->orig);
    a = length_squared(vec_cross(ray->dir, cylinder->dir));
    half_b = vec_dot(vec_cross(ray->dir, cylinder->dir), vec_cross(oc, cylinder->dir));
    c = length_squared(vec_cross(oc, cylinder->dir)) - (cylinder->rad * cylinder->rad);
    discriminant = (half_b * half_b) - (a * c);

    if (discriminant < 0)
        return (0);
    sqrtd = sqrt(discriminant);
    root = (-half_b - sqrtd) / a;
    
    //뚜껑이 있다면 원기둥의 안쪽면까지 표현할 필요는 없음.
    h = sqrt(length_squared(vec_sub(ray_at(ray, root), cylinder->orig)) - (cylinder->rad * cylinder->rad));
    if (root < rec->t_min || root > rec->t_max || h > cylinder->half_h)
    {    
        root = (-half_b + sqrtd) / a;
        h = sqrt(length_squared(vec_sub(ray_at(ray, root), cylinder->orig)) - (cylinder->rad * cylinder->rad));
        if (root < rec->t_min || root > rec->t_max || h > cylinder->half_h)
            return (0);
    }
    if (h > cylinder->half_h)
        return (0);
    //

    //뚜껑이 있을때
    // if (root < rec->t_min || root > rec->t_max)
    // {
    //     root = -half_b + sqrtd;
    //     if (root < rec->t_min || root > rec->t_max)
    //         return (0);
    // }
    // h = sqrt(length_squared(vec_sub(ray_at(ray, root), cylinder->orig)) - (cylinder->rad * cylinder->rad));
    // if (h > cylinder->half_h)
    //     return (0);
    //

    rec->p = ray_at(ray, root);
    rec->t = root;
    rec->t_max = rec->t;

    if (vec_dot(vec_sub(rec->p, cylinder->orig), cylinder->dir) < 0)
        h *= -1;
    f = vec_sum(cylinder->orig, vec_mul(cylinder->dir, h));
    //lenght_squared(p - c) - (rad * rad)
    rec->normal = vec_div(vec_sub(rec->p, f), cylinder->rad);
    // rec->normal = vec_div(vec_sub(rec->p, cylinder->orig), cylinder->rad);
    rec->albedo = cylinder->albedo;

    return (1);
}

/*
t = |b|
a * b = |a| * |b| * cos
dot(a,b) / (len(a) * len(b)) = cos
cos' / cos
*/