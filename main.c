#include "minirt.h"

int main()
{
    t_image img;
    t_camera cam;
    t_ray ray;
    t_vec orig;
    t_color color;

    int j;
    int i;
    double u;
    double v;

    orig = vec(1, 2, 3);
    img = image(400, 16 / 9);
    cam = camera(&orig, 70.0, img.aspect_ratio);

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