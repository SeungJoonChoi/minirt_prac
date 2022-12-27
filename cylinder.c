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

    int ret;

    oc = vec_sub(ray->orig, cylinder->orig);
    a = length_squared(vec_cross(ray->dir, cylinder->dir));
    half_b = vec_dot(vec_cross(ray->dir, cylinder->dir), vec_cross(oc, cylinder->dir));
    c = length_squared(vec_cross(oc, cylinder->dir)) - (cylinder->rad * cylinder->rad);
    discriminant = (half_b * half_b) - (a * c);

    if (discriminant < 0)
        ret = 0;
    else
        ret = 1;
    sqrtd = sqrt(discriminant);
    root = (-half_b - sqrtd) / a;
    
    h = sqrt(length_squared(vec_sub(ray_at(ray, root), cylinder->orig)) - (cylinder->rad * cylinder->rad));
    if (root < rec->t_min || root > rec->t_max || h > cylinder->half_h)
    {    
        root = (-half_b + sqrtd) / a;
        h = sqrt(length_squared(vec_sub(ray_at(ray, root), cylinder->orig)) - (cylinder->rad * cylinder->rad));
        if (root < rec->t_min || root > rec->t_max || h > cylinder->half_h)
            ret = 0;
    }
    if (h > cylinder->half_h)
        ret = 0;


    if (ret)
    {
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
    }
    if (hit_circle(ray, cylinder, rec))
        return (1);

    return (ret);
}

/*
t = |b|
a * b = |a| * |b| * cos
dot(a,b) / (len(a) * len(b)) = cos
cos' / cos

t = ((C - O) * N) / (D * N) (t를 (C - O)에 곱하면 광선의 길이를 구할 수 있음)
*/

int hit_circle(t_ray *ray, t_cylinder *cylinder, t_hit_record *rec)
{
    t_vec c;
    // t_vec root;
    // t_vec fo;
    // double cos;
    // double t;
    if (vec_dot(ray->dir, cylinder->dir) > 0)
        cylinder->dir = vec_mul(cylinder->dir, -1);
    c = vec_sum(cylinder->orig, vec_mul(cylinder->dir, cylinder->half_h));
    // fo = vec_sub(ray->orig, f);
    // t = vec_length(fo);
    // cos = vec_dot(cylinder->dir, fo);

    double root;
    t_vec oc;

    oc = vec_sub(c, ray->orig);
    root = vec_dot(vec_unit(oc), cylinder->dir) / vec_dot(ray->dir, cylinder->dir);
    root *= vec_length(oc);

    // root = vec_sum(ray->orig, vec_mul(ray->dir, t));
    
    if (root < rec->t_min || root > rec->t_max || vec_length(vec_sub(ray_at(ray, root), c)) > cylinder->rad)
    {
        c = vec_sum(cylinder->orig, vec_mul(cylinder->dir, -(cylinder->half_h)));
        oc = vec_sub(c, ray->orig);
        root = vec_dot(vec_unit(oc), cylinder->dir) / vec_dot(ray->dir, cylinder->dir);
        root *= vec_length(oc);
        if (root < rec->t_min || root > rec->t_max || vec_length(vec_sub(ray_at(ray, root), c)) > cylinder->rad)
                return (0);
        // return (0);
    }

    rec->p = ray_at(ray, root);
    rec->t = root;
    rec->t_max = rec->t;
    rec->normal = cylinder->dir; // 검증
    rec->albedo = cylinder->albedo;

    return (1);
}