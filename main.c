#include "minirt.h"

static int key_press(int keycode, t_vars *vars)
{
    if (keycode == KEY_ESC)
    {
        mlx_destroy_window(vars->mlx, vars->win);
        exit(0);
    }
    return (0);
}

static int close(t_vars *vars)
{
    mlx_destroy_window(vars->mlx, vars->win);
    exit(0);
    return (0);
}

int main()
{
    t_data data;
    t_image img;
    t_camera cam;
    t_ray ray;
    t_vec orig;
    t_color color;
    t_vars vars;

    int j;
    int i;
    double u;
    double v;

    orig = vec(1, 2, 3);
    img = image(1200, 16.0 / 9.0);
    cam = camera(&orig, 70.0, img.aspect_ratio);

    vars.mlx = mlx_init();
    vars.win = mlx_new_window(vars.mlx, img.image_width, img.image_height, "seunchoi_minirt");
    data.img = mlx_new_image(vars.mlx, img.image_width, img.image_height);
    data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);
    
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
            // mlx_pixel_put(mlx_ptr, mlx_win, i, img.image_height - 1 - j, rgb_to_int(0.0, &color));
            my_mlx_pixel_put(&data, i, img.image_height - 1 - j, rgb_to_int(0.0, &color));
            ++i;
        }
        --j;
    }

    mlx_put_image_to_window(vars.mlx, vars.win, data.img, 0, 0);
    mlx_hook(vars.win, X_EVENT_KEY_PRESS, 0, &key_press, &vars);
    mlx_hook(vars.win, X_EVENT_KEY_EXIT, 0, &close, &vars);
    mlx_loop(vars.mlx);
    
    return (0);
}