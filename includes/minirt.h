#ifndef MINIRT_H
#define MINIRT_H

#include <math.h>
#define degToRad(angleInDegrees) ((angleInDegrees) * M_PI / 180.0)
#define radToDeg(angleInRadians) ((angleInRadians) * 180.0 / M_PI)

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

typedef struct s_image
{
    double aspect_ratio;
    int image_width;
    int image_height;
} t_image;

typedef struct s_camera
{
    t_vec orig;
    double viewport_height;
    double viewport_width;
    double focal_length;
} t_camera;

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
//ray.c
t_ray ray(t_vec *origin, t_vec* direction);
t_vec ray_at(t_ray *ray, double t);
//camera.c
t_camera camera(t_vec *orig, double fov, double aspect_ratio);
//image.c
t_image image(int width, double aspect_ratio);


#endif