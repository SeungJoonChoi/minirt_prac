#include "minirt.h"

int main()
{
    t_image img;
    t_camera cam;
    t_ray ray;
    t_vec orig;
    t_color color;

    void *mlx_ptr;
    void *mlx_win;

    int j;
    int i;
    double u;
    double v;

    orig = vec(1, 2, 3);
    img = image(1200, 16.0 / 9.0);
    cam = camera(&orig, 70.0, img.aspect_ratio);

    mlx_ptr = mlx_init();
    mlx_win = mlx_new_window(mlx_ptr, img.image_width, img.image_height, "seunchoi_minirt");
    mlx_loop(mlx_ptr);

    j = img.image_height - 1;
    while (j >= 0)
    {
        i = 0;
        while (i < img.image_width)
        {
            u = (double)i / (double)(img.image_width - 1);
            v = (double)j / (double)(img.image_height - 1);
            ray = ray_viewport(&cam, u, v);
            color = ray_color(&ray);
            ++i;
        }
        --j;
    }
    
    return (0);
}