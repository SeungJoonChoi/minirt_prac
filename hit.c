#include "minirt.h"

static int hit_obj(t_ray *ray, t_obj *obj, t_hit_record *rec)
{
    if (obj->type == SPHERE)
        return (hit_sphere(ray, obj->element, rec));
    // if (type == ???) ...
    return (0);
}

int hit(t_ray *ray, t_obj *head, t_hit_record *rec)
{
    t_obj *cur;
    int hit_flag;

    hit_flag = 0; //맞았는지 확인
    cur = head->next;
    rec->t_min = 0; //가시거리의 최소값
    rec->t_max = INFINITY; //가시거리의 최댓값
    while (cur != NULL)
    {
        if (hit_obj(ray, cur, rec)) //오브젝트에 맞았다면 rec에 기록하고 1을 반환
            hit_flag = 1;
        cur = cur->next;
    }
    return (hit_flag);
}