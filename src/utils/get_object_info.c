#include "minirt.h"

t_vec3 get_position(t_object *object)
{
	t_sphere *sphere;
	t_plan *plane;
	t_cylindre *cylinder;

	if (object->type == SPHERE)
	{
		sphere = (t_sphere *)object->obj;
		return (sphere->position);
	}
	if (object->type == PLAN)
	{
		plane = (t_plan *)object->obj;
		return (plane->position);
	}
	if (object->type == CYLINDRE)
	{
		cylinder = (t_cylindre *)object->obj;
		return (cylinder->position);
	}
	return(null_vector());
}

t_color get_obj_color(t_object *obj)
{
	t_sphere *sphere;
	t_plan *plane;
	t_cylindre *cylindre;
	t_color color;

	if (obj->type == SPHERE)
	{
		sphere = (t_sphere *)obj->obj;
		color = sphere->color;
		return (color);
	}
	else if (obj->type == PLAN)
	{
		plane = (t_plan *)obj->obj;
		return (plane->color);
	}
	else if (obj->type == CYLINDRE)
	{
		cylindre = (t_cylindre *)obj->obj;
		return (cylindre->color);
	}
	else
		return (no_color());
}