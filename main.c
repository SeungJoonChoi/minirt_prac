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
    
    // t_ray ray;
    t_color pixel_color;
    t_vars vars;

    t_scene scene;

    scene = scene_init(image(1920, 1080), camera(vec(0, 0, 0), \
    vec(0, 0, 1), 90.0, 1920.0 / 1080.0), 0.1, color(1, 1, 1));

    //object
    obj_add(&scene.world, SPHERE, sphere(vec(-25, 0, 150), 50, color(0.7, 0.2, 0.2)));
    obj_add(&scene.world, SPHERE, sphere(vec(75, 0, 150), 50, color(0.2, 0.7, 0.2)));
    obj_add(&scene.world, SPHERE, sphere(vec(0, 50, 150), 50, color(0.2, 0.2, 0.7)));

    //light
    obj_add(&scene.light, POINT, point_light(vec(-100, 50, 80), color(1, 1, 1), 0.6));
    obj_add(&scene.light, POINT, point_light(vec(100, -50, 100), color(1, 0, 0), 0.6));

    int j;
    int i;
    double u;
    double v;



    vars.mlx = mlx_init();
    vars.win = mlx_new_window(vars.mlx, scene.image.image_width, scene.image.image_height, "seunchoi_minirt");
    data.img = mlx_new_image(vars.mlx, scene.image.image_width, scene.image.image_height);
    data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);
    
    // 뷰포트의 왼쪽하단부터 그리기 위해 i = 0, j = 높이 부터 시작
    j = scene.image.image_height - 1;
    while (j >= 0)
    {
        i = 0;
        while (i < scene.image.image_width)
        {
            u = (double)i / (double)(scene.image.image_width - 1);
            v = (double)j / (double)(scene.image.image_height - 1);
            scene.ray = ray_viewport(&scene.camera, u, v);
            pixel_color = ray_color(&scene);
            // mlx_pixel_put(mlx_ptr, mlx_win, i, img.image_height - 1 - j, rgb_to_int(0.0, &color));
            my_mlx_pixel_put(&data, i, scene.image.image_height - 1 - j, rgb_to_int(0.0, &pixel_color));
            ++i;
        }
        --j;
    }

    mlx_put_image_to_window(vars.mlx, vars.win, data.img, 0, 0);
    mlx_hook(vars.win, X_EVENT_KEY_PRESS, 0, &key_press, &vars);
    mlx_hook(vars.win, X_EVENT_KEY_EXIT, 0, &close, &vars);
    mlx_loop(vars.mlx);

    obj_clear(&scene.world);

    return (0);
}