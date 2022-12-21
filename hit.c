#include "minirt.h"

static int hit_obj(t_ray *ray, t_obj *obj, t_hit_record *rec)
{
    if (obj->type == SPHERE)
        return (hit_sphere(ray, obj->element, rec));
    return (0);
}

int hit(t_ray *ray, t_obj *head, t_hit_record *rec)
{
    t_obj *cur;
    int hit_flag;

    hit_flag = 0;
    cur = head->next;
    rec->t_min = 0;
    rec->t_max = INFINITY;
    while (cur != NULL)
    {
        if (hit_obj(ray, cur, rec))
        {
            hit_flag = 1;
            rec->t_max = rec->t;
        }
        cur = cur->next;
    }
    return (hit_flag);
}