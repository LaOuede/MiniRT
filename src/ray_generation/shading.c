#include "minirt.h"

t_vec3 get_light_dir(t_hit *hit, void *current_light)
{
	t_vec3 w;
	t_vec3 light_position;

	light_position = get_light_position(current_light);

	w = vec_subs(light_position, hit->hit_point);
	w = vec_norm(w);
	return (w);
}

float get_geo_term(t_hit *hit, void *current_light, t_vec3 n)
{
	t_vec3 w;
	float geo_term;

	w = get_light_dir(hit, current_light);
	geo_term = vec_dot(n, w);
	return (geo_term);
}

static bool shadow_ray_hits(t_hit *hit, void *light)
{
	t_vec3 light_position;
	t_vec3 d;
	float t;
	t_list *current;
	void *object;
	t_hit new_hit;

	light_position = get_light_position(light);
	d = vec_norm(vec_subs(light_position, hit->hit_point));
	t = vec_mag(vec_subs(light_position, hit->hit_point));

	current = get_minirt()->objects;
	while (current)
	{
		if (get_obj_material(current->content)->id == SUN
			|| hit->obj->obj == current->content)
		{
			current = current->next;
			continue ;
		}
		object = current->content;
		find_hit(d, object, &new_hit, hit->hit_point);
		if (new_hit.obj && new_hit.t < t)
			return (TRUE);
		current = current->next;
	}
	return (FALSE);
}

void add_light_color(t_shading *shade, void *light, float light_intensity, int refl)
{
	t_color coloradd;

	if (refl > 1)////
		return;
	light_intensity /=  255.0f;
	// if (light_intensity > 0 && light_intensity < 0.2f)
	// 	light_intensity = 0.2f;
	// if (light_intensity <= 0)
	// 	light_intensity = 0.1f;
	coloradd = color_scale(get_light_color(light), light_intensity);
	shade->color = color_add(shade->color, coloradd);
	coloradd = color_scale(get_minirt()->ambiant_light.color , get_minirt()->ambiant_light.intensity);
	shade->color = color_add(shade->color, coloradd);

}

float shading_intensity(t_hit *hit, t_vec3 n, t_shading *shade, int refl)
{
	t_list *current;
	float diffuse_light;
	float ambiant_light;
	float light_intensity;
	float current_intensity;
	float geo_term;

	ambiant_light = 255.0f * get_minirt()->ambiant_light.intensity;
	light_intensity = ambiant_light;
	if (get_obj_material(hit->obj)->id == SUN)
		return (255.0f);
	current = get_minirt()->lights;
	while (current)
	{
		if (shadow_ray_hits(hit, current->content))
		{
			current = current->next;
			continue;
		}
		geo_term = get_geo_term(hit, current->content, n);
		if (geo_term >= 0.0f)
			diffuse_light = geo_term * 255.0f * get_light_intensity(current->content);/////
		else
			diffuse_light = 0.0f;
		current_intensity = diffuse_light;
		if (current_intensity > 255.0f)
			current_intensity = 255.0f;
		if (current_intensity < ambiant_light)
			current_intensity = ambiant_light;
		add_light_color(shade, current->content, current_intensity, refl);
		if (current_intensity > light_intensity)
			light_intensity = current_intensity;
		
		current = current->next;
	}
	
	return (light_intensity);
}

void calc_specular_effect(t_hit *hit, t_vec3 n, t_vec3 v, t_shading *shade)
{
	t_color specular_color;
	t_vec3	h;
	t_vec3	w;
	float	coeff;
	float	current_coeff;
	t_list *current;
	float	light_intensity;

	light_intensity = 0.0f;
	specular_color = get_specular_color(shade->color, hit, shade);
	// specular_color = color_scale(generate_color(100.0f, 100.0f, 100.0f), get_obj_material(hit->obj)->specular_factor);
	current = get_minirt()->lights;
	coeff = 0;
	while (current)
	{
		w = get_light_dir(hit, current->content);
		h = vec_norm(vec_add(w, v));
		current_coeff = vec_dot(n, h);
		if (current_coeff < 0)
			current_coeff = 0;
		// current_coeff = pow(current_coeff, get_obj_material(hit->obj)->shine);
		current_coeff = pow(current_coeff, get_obj_material(hit->obj)->shine * pow(get_light_intensity(current->content), 1.4f));
		if (current_coeff > coeff)
		{
			coeff = current_coeff;
			light_intensity = get_light_intensity(current->content) * 255.0f;
		}
		current = current->next;
	}
	// coeff *= shade->intensity / 255.0f;
	// shade->color = color_scale(specular_color, shading_intensity(hit, n) / 255.0f);
	// if (light_intensity * 255.0f * coeff > shade->intensity)
	// 	shade->intensity = light_intensity * 255.0f * coeff;
	
			// if (light_intensity * 255.0f * coeff >= shade->intensity && coeff > 0.01)
			// 	shade->intensity = light_intensity * 255.0f *coeff;
			float diff;
			diff = light_intensity - shade->intensity;
			shade->intensity += MAX(coeff, 0.1) * diff;
	shade->color = color_add(shade->color, color_scale(specular_color, coeff));
}

// t_color shading_color(t_hit *hit, t_vec3 w, t_vec3 n, t_color obj_color)
// {
// 	t_color specular_color;
// 	t_color output_color;
// 	t_vec3	v;
// 	t_vec3	h;
// 	float	coeff;

// 	specular_color = get_specular_color();

// 	v = vec_norm(vec_subs(get_minirt()->camera.position, hit->hit_point));
// 	h = vec_norm(vec_add(w, v));


// 	coeff = vec_dot(n, h);
// 	if (coeff < 0)
// 		coeff = 0;
// 	coeff = pow(coeff, get_obj_material(hit->obj)->shine * pow(get_light_intensity(get_minirt()->lights->content), 1.4f));

// 	specular_color = color_scale(specular_color, coeff);

// 	output_color = color_add(obj_color, specular_color);

// 	output_color = max_color(output_color);
// 	return(output_color);
// }

t_color shading_color(t_hit *hit, t_vec3 n, t_shading *shade, int *refl, t_vec3 v)
{
	t_material *mat;

	mat = get_obj_material(hit->obj);
	if (mat->shine != 0)
		calc_specular_effect(hit, n, v, shade);//!!!!IMPORTANT!!!!<------------------
	if (mat->reflexion != 0)
		calc_reflexion(hit, n, v, shade, refl);

	return(shade->color);
}


t_shading shading(t_hit *hit)
{
	t_vec3 		n;
	t_shading	shade;
	int refl;
	t_vec3	v;
	t_color coloradd;

	v = vec_norm(vec_subs(get_minirt()->camera.position, hit->hit_point));

	refl = 0;
	
	shade.color = get_texture_color(hit);

	n = get_normal_vec(hit);
	shade.intensity = shading_intensity(hit, n, &shade, refl);
	shade.color = shading_color(hit, n, &shade, &refl, v);
	coloradd = color_scale(get_minirt()->ambiant_light.color , get_minirt()->ambiant_light.intensity);
	shade.color = color_add(shade.color, coloradd);

	shade.color = max_color(shade.color);

	return (shade);
}
