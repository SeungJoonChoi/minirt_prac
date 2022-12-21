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
    t_vec color;
    t_vars vars;

    //obj list temp
    t_obj head;
    t_obj obj1;
    t_obj obj2;
    t_sphere s1;
    t_sphere s2;

    s1.orig = vec(-25, 0, 100);
    s1.rad = 50;

    s2.orig = vec(75, 0, 100);
    s2.rad = 50;

    obj1.type = SPHERE;
    obj1.element = &s1;

    obj2.type = SPHERE;
    obj2.element = &s2;

    head.next = &obj1;
    head.next->next = &obj2;
    head.next->next->next = NULL;
    //////////

    int j;
    int i;
    double u;
    double v;

    img = image(1600, 16.0 / 9.0);
    cam = camera(vec(0, 0, 0), vec(0, 0, 1), 90.0, img.aspect_ratio);

    vars.mlx = mlx_init();
    vars.win = mlx_new_window(vars.mlx, img.image_width, img.image_height, "seunchoi_minirt");
    data.img = mlx_new_image(vars.mlx, img.image_width, img.image_height);
    data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);
    
    // 뷰포트의 왼쪽하단부터 그리기 위해 i = 0, j = 높이 부터 시작
    j = img.image_height - 1;
    while (j >= 0)
    {
        i = 0;
        while (i < img.image_width)
        {
            u = (double)i / (double)(img.image_width - 1);
            v = (double)j / (double)(img.image_height - 1);
            ray = ray_viewport(&cam, u, v);
            color = ray_color(ray, &head);
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