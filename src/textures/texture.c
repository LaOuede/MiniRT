#include "minirt.h"


t_color get_texture_color(t_hit *hit)
{
	t_minirt *minirt;
	t_material *mat;
	t_color color;
	unsigned int px;
	unsigned int py;
	unsigned int p_xy;

	minirt = get_minirt();
	mat = get_obj_material(hit->obj);
	uv_map_sphere(hit, &px, &py, mat->texture);//could be any texture
	p_xy = 4 * (py * mat->texture->width + px);
	
	color.r = mat->texture->pixels[p_xy];
	color.g = mat->texture->pixels[p_xy + 1];
	color.b = mat->texture->pixels[p_xy + 2];
	return (color);
}
