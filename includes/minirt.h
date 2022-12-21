#ifndef MINIRT_H
#define MINIRT_H

#define degToRad(angleInDegrees) ((angleInDegrees) * M_PI / 180.0)
#define radToDeg(angleInRadians) ((angleInRadians) * 180.0 / M_PI)

#include "mlx.h"
#include <math.h>
#include <stdlib.h>

# define X_EVENT_KEY_PRESS		2
# define X_EVENT_KEY_EXIT		17

# define KEY_ESC			53

typedef struct s_vars
{
    void *mlx;
    void *win;
} t_vars;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
} t_data;

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
    t_vec w;
    t_vec u;
    t_vec v;
    t_vec horizontal;
    t_vec vertical;
    t_vec lower_left_corner;
} t_camera;

typedef struct s_color
{
    double r;
    double g;
    double b;
} t_color;

//vec1.c
t_vec vec(double x, double y, double z);
t_vec vec_sum(t_vec vec1, t_vec vec2);
t_vec vec_sub(t_vec vec1, t_vec vec2);
t_vec vec_mul(t_vec vec, double t);
t_vec vec_div(t_vec vec, double t);
//vec2.c
double vec_dot(t_vec vec1, t_vec vec2);
t_vec vec_cross(t_vec vec1, t_vec vec2);
double vec_length(t_vec vec);
t_vec vec_unit(t_vec vec);
//ray.c
t_ray ray_set(t_vec *origin, t_vec* direction);
t_vec ray_at(t_ray *ray, double t);
t_ray ray_viewport(t_camera *camera, double u, double v);
//camera.c
t_vec lower_left_corner(t_camera *camera);
t_camera camera(t_vec orig, t_vec dir, double fov, double aspect_ratio);
//image.c
t_image image(int width, double aspect_ratio);
//color.c
t_color color(double r, double g, double b);
t_color ray_color(t_ray ray);
//mlx_utils.c
int rgb_to_int(double trans, t_color *color);
void my_mlx_pixel_put(t_data *data, int x, int y, int color);
//sphere.c
double hit_sphere(t_vec center, double radius, t_ray ray);

#endif