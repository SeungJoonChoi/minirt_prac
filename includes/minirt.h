#ifndef MINIRT_H
#define MINIRT_H

#include <math.h>

typedef struct s_vec
{
    double x;
    double y;
    double z;
} t_vec;

t_vec vec(double x, double y, double z);
t_vec vec_sum(t_vec *vec1, t_vec *vec2);
t_vec vec_sub(t_vec *vec1, t_vec *vec2);
t_vec vec_mul(t_vec *vec, double t);
t_vec vec_div(t_vec *vec, double t);

#endif