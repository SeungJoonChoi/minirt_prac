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
    {
        ret = 1;
        sqrtd = sqrt(discriminant);
        root = (-half_b - sqrtd) / a;
        
        if (root < rec->t_min || root > rec->t_max)
        {    
            root = (-half_b + sqrtd) / a;
            if (root < rec->t_min || root > rec->t_max)
                ret = 0;
        }
        h = sqrt(length_squared(vec_sub(ray_at(ray, root), cylinder->orig)) - (cylinder->rad * cylinder->rad));
        if (h > cylinder->half_h)
            ret = 0;
    }


    if (ret)
    {
        rec->p = ray_at(ray, root);
        rec->t = root;
        rec->t_max = rec->t;

        if (vec_dot(vec_sub(rec->p, cylinder->orig), cylinder->dir) < 0)
            h *= -1; //p가 원기둥의 아랫부분에 있다면 원기둥의 반대 방향으로 h를 곱해줌.
        f = vec_sum(cylinder->orig, vec_mul(cylinder->dir, h));
        rec->normal = vec_div(vec_sub(rec->p, f), cylinder->rad);
        rec->albedo = cylinder->albedo;
    }
    if (hit_circle(ray, cylinder, rec))
        return (1);

    return (ret);
}

/*
hit_circle

t = cos' / cos
t = ((C - O) * N) / (D * N) (t를 (C - O)에 곱하면 광선의 길이를 구할 수 있음)

'ray.orig에서 circle의 중심까지의 벡터(C - O)'와 'circle의 법선벡터(N)'를 내적하여 cos'값을 구할 수 있음
'ray.dir와 N을 내적'하여 cos을 구한 뒤 cos과 cos'의 비율을 이용하여 t를 구할 수 있음.

//https://oopy.lazyrockets.com/api/v2/notion/image?src=https%3A%2F%2Fs3-us-west-2.amazonaws.com%2Fsecure.notion-static.com%2Fe8d52994-5a38-49a0-9340-095c67252e4c%2FUntitled.png&blockId=2f330399-e614-473e-8302-8372bea26d9d
*/

int hit_circle(t_ray *ray, t_cylinder *cylinder, t_hit_record *rec)
{
    t_vec c;
    double parallel;
    double root;
    t_vec oc;

    parallel = vec_dot(ray->dir, cylinder->dir); //원판이 ray와 평행하다면 계산할 필요 없음
    if (parallel == 0)
        return (0);

    if (parallel > 0) //원기둥은 위아래 대칭이기 때문에 윗부분이 카메라와 마주보도록 뒤집어줌
        cylinder->dir = vec_mul(cylinder->dir, -1);
    c = vec_sum(cylinder->orig, vec_mul(cylinder->dir, cylinder->half_h)); //원판의 중심
    oc = vec_sub(c, ray->orig);
    root = vec_dot(vec_unit(oc), cylinder->dir) / vec_dot(ray->dir, cylinder->dir); // t = cos' / cos
    root *= vec_length(oc); // 계산에 이용된 값을 모두 단위벡터로 했기 때문에 실제로 '비율'만 구해짐. 이 비율을 oc의 길이에 곱해줘서 P(t)의 길이를 알아냄.
    
    if (root < rec->t_min || root > rec->t_max || vec_length(vec_sub(ray_at(ray, root), c)) > cylinder->rad)
    //t가 범위안에 있는지와 더불어 원판의 범위(반지름)을 넘어가는지도 확인해줌
    {
        //t가 범위안에 없다면 원기둥의 윗부분이 카메라 뒤에 있다는 뜻이므로 아랫부분의 원판의 t는 범위안에 있는지 확인해줌
        cylinder->dir = vec_mul(cylinder->dir, -1);
        c = vec_sum(cylinder->orig, vec_mul(cylinder->dir, cylinder->half_h));
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
    rec->normal = cylinder->dir;
    rec->albedo = cylinder->albedo;

    return (1);
}