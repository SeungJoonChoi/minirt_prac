#ifndef MINIRT_H
#define MINIRT_H

#include <math.h>

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

//vec1.c
t_vec vec(double x, double y, double z);
t_vec vec_sum(t_vec *vec1, t_vec *vec2);
t_vec vec_sub(t_vec *vec1, t_vec *vec2);
t_vec vec_mul(t_vec *vec, double t);
t_vec vec_div(t_vec *vec, double t);
//vec2.c
double vec_dot(t_vec *vec1, t_vec *vec2);
t_vec vec_cross(t_vec *vec1, t_vec *vec2);
double vec_length(t_vec *vec);
t_vec vec_unit(t_vec *vec);

#endif