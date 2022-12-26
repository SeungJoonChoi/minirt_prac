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
    if (root < rec->t_min || root > rec->t_max)
    {
        root = (-half_b + sqrtd) / a;
        if (root < rec->t_min || root > rec->t_max)
            return (0);
    }
    rec->t = root;
    rec->t_max = rec->t;
    rec->p = ray_at(ray, root);
    h = sqrt(length_squared(vec_sub(rec->p, cylinder->orig)) - (cylinder->rad * cylinder->rad));
    f = vec_sum(cylinder->orig, vec_mul(cylinder->dir, h));
    //lenght_squared(p - c) - (rad * rad)
    rec->normal = vec_div(vec_sub(rec->p, f), cylinder->rad);
    rec->albedo = cylinder->albedo;

    return (1);
}