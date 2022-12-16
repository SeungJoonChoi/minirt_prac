#include <stdio.h>

typedef struct s_vec
{
    double x;
    double y;
    double z;
} t_vec;

typedef struct s_ray
{
    t_vec orig;
    t_vec dir;
} t_ray;

t_vec vec(double x, double y, double z)
{
    t_vec ret;
    
    ret.x = x;
    ret.y = y;
    ret.z = z;
    return (ret);
}

t_ray ray(t_vec *origin, t_vec* direction)
{
    t_ray ret;

    ret.orig = *origin;
    ret.dir = *direction;
    return (ret);
}

int main()
{
    t_vec orig = vec(1, 2, 3);
    t_vec dir = vec(0, 0, 1);
    t_ray ray1;
    t_ray ray2;

    ray1 = ray(&orig, &dir);
    ray2 = ray(&orig, &dir);

    printf("orig : %p\n", &orig);
    printf("ray1 : %p\n", &(ray1.orig));
    printf("ray2 : %p\n", &(ray2.orig));

    return 0;
}