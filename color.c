#include "minirt.h"

t_vec color(double r, double g, double b)
{
    t_vec ret;

    ret.x = r;
    ret.y = g;
    ret.z = b;
    return (ret);
}

t_vec ray_color(t_ray ray, t_obj *head)
{
    t_vec unit_vec;
    double t;
    // double r;
    t_hit_record rec;
    // int hit_flag;
    // t_obj *current;

    // current = head->next;
    // hit_flag = 0;
    // rec.t = 0;
    // rec.t_min  = 0;
    // rec.t_max = INFINITY;
    // while (current != NULL)
    // {
    //     if (hit_sphere(&ray, current->element, &rec))
    //     {
    //         rec.t_max = rec.t;
    //         hit_flag = 1;
    //     }
    //     current = current->next;
    // }
    // hit_flag = hit(&ray, head, &rec);

    if (hit(&ray, head, &rec))
    {
        unit_vec = vec_unit(vec_sum(rec.normal, vec(0, 0, 4)));
        return (vec_mul(vec_sum(unit_vec, vec(1, 1, 1)), 0.5));
    }

    // if (hit_sphere(vec(0, 0, 8), 3.0, ray))
    //     return (color(1.0, 0.0, 0.0));
    unit_vec = vec_unit(ray.dir);
    t = 0.5 * (unit_vec.y + 1.0);
    return (vec(1.0 - (0.5 * t), 1.0 - (0.3 * t), 1.0));
}