#include "minirt.h"

/*
Combines four individual channel bytes into a single integer using
bit-shifting
Use with mlx_put_pixel as 4th param (uint_32 color)

*** I think we don't need a so it will be silenced and assigned to 0 ???***

*/
int	get_rgba(t_color color, float a)
{
	return ((int)color.r << 24 | (int)color.g << 16 | (int)color.b << 8 | (int)a);
}

t_color no_color(void)
{
	t_color color;

	color.r = 0;
	color.g = 0;
	color.b = 0;
	return(color);
}

t_color get_specular_color(void)
{
	t_color color;
	float color_intensity;

	color_intensity = pow(get_light_intensity(get_minirt()->lights->content), 1.2) * 255.0f * 0.2f;
	color.r = color_intensity;
	color.b = color_intensity;
	color.g = color_intensity;
	return(color);
}

t_color max_color(t_color color)
{
	if (color.r >= 255.0f)
		color.r = 254.9f;
	if (color.g >= 255.0f)
		color.g = 254.9f;
	if (color.b >= 255.0f)
		color.b = 254.9f;
	return (color);
}

t_color	color_scale(t_color v, float scale)
{
	t_color	res;

	res.r = v.r * scale;
	res.g = v.g * scale;
	res.b = v.b * scale;
	return (res);
}

t_color	color_add(t_color v1, t_color v2)
{
	t_color	res;

	res.r = v1.r + v2.r;
	res.g = v1.g + v2.g;
	res.b = v1.b + v2.b;
	return (res);
}

t_color	data_to_rgb(const unsigned int color)
{
	t_color		rgb;

	rgb.r = ((color >> 16) & 0xFF) / 255.0;
	rgb.g = ((color >> 8) & 0xFF) / 255.0;
	rgb.b = ((color) & 0xFF) / 255.0;
	return (rgb);
}

/*
SCALE
*/
// int	color_scale(t_color col1, float scale)
// {
// 	t_color	new;

// 	new.r = col1.r * scale;
// 	new.g = col1.g * scale;
// 	new.b = col1.b * scale;
// 	return (get_rgba(new.r, new.g, new.b, 0));
// }
