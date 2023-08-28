#include "minirt.h"

void load_moon(void)
{
	t_minirt *minirt;

	minirt = get_minirt();
	minirt->material[MOON].id = MOON;
	minirt->material[MOON].texture = mlx_load_png("textures_png/moon/moon_texture.png");
	minirt->material[MOON].norm_map = mlx_load_png("textures_png/moon/moon_normap_5.png");
	minirt->material[MOON].shine = 0;//?
	minirt->material[MOON].reflexion = 0.4;//?
	minirt->material[WATER].specular_factor = 0;//?
}
