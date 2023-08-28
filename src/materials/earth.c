#include "minirt.h"

void load_earth(void)
{
	t_minirt *minirt;

	minirt = get_minirt();
	minirt->material[EARTH].id = EARTH;
	minirt->material[EARTH].texture = mlx_load_png("textures_png/earth/new_earth_texture.png");
	minirt->material[EARTH].norm_map = mlx_load_png("textures_png/earth/earth_normap.png");
	minirt->material[EARTH].shine = 1000;//?
	minirt->material[EARTH].reflexion = 0.00000000001;//?
	minirt->material[EARTH].specular_factor = 0.5;//?

}
