
#include "minirt.h"


//parses line input to the sphere struct
void parse_sphere(char **line, t_object *object)
{
	t_sphere *sphere;

	sphere = (t_sphere*)object->obj;
	check_error(line, SPHERE, object);
	
	// check_sphere_validity(line);
	
	parse_coordinates(line[1], &sphere->position);
	sphere->rayon = ft_atof(line[2]) / 2;
	parse_colors(line[3], &sphere->color);
}

//parses line input to the cylinder struct
void parse_cylinder(char **line, t_object *object)
{
	t_cylindre *cylindre;

	cylindre = (t_cylindre*)object->obj;
	check_error(line, CYLINDRE, object);
	//check if valid

	parse_coordinates(line[1], &cylindre->position);
	parse_coordinates(line[2], &cylindre->direction);
	cylindre->rayon = ft_atof(line[3]) / 2;
	cylindre->hauteur = ft_atof(line[4]);
	parse_colors(line[5], &cylindre->color);
}

//parses line input to the plane struct
void parse_plane(char **line, t_object *object)
{
	t_plan *plan;

	plan = (t_plan*)object->obj;
	check_error(line, PLAN, object);
		
	parse_coordinates(line[1], &plan->position);
	parse_coordinates(line[2], &plan->direction);
	parse_colors(line[3], &plan->color);
}
