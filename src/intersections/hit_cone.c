#include "minirt.h"

t_vec3	calc_normal_cone(t_qdt q, t_hit *hit, t_cone *cone, t_object *packed_cone)
{
	t_vec3	n;
	t_vec3	disp;
	t_vec3	hit_point;

	hit_point = vec_add(q.origin, vec_scale(q.d, hit->t));
	disp = vec_subs(hit_point, cone->position);
	n = vec_norm(vec_subs(disp, vec_scale(vec_norm(cone->direction), \
		vec_dot(disp, vec_norm(cone->direction)))));
	return (n);
}

static void	hit_cone_norm(t_qdt q, t_hit *hit, t_cone *cone, \
	t_object *packed_cone)
{
	if (q.t < 0.00001 || fabs(q.m) > cone->hauteur / 2)
	{
		q.t = (-q.half_b + sqrtf(q.discriminant)) / q.a;
		q.m = vec_dot(q.d, vec_norm(cone->direction)) * q.t + \
			vec_dot(q.disp, vec_norm(cone->direction));
		if (q.t < 0.00001 || fabs(q.m) > cone->hauteur / 2)
		{
			hit->obj = NULL;
			hit->t = ERROR;
			return ;
		}
		else
		{
			hit->obj = packed_cone;
			hit->t = q.t;
			hit->normal = calc_normal_cone(q, hit, cone, packed_cone);
		}
	}
	else
	{
		hit->obj = packed_cone;
		hit->t = q.t;
		hit->normal = calc_normal_cone(q, hit, cone, packed_cone);
	}
}

/*
Equation :
	a = D|D - (1+k*k)*(D|V)^2
	b/2 = D|X - (1+k*k)*(D|V)*(X|V)
	c = X|X - (1+k*k)*(X|V)^2
	t = (-b - √d) / a; OUTSIDE
	t = (-b + √d) / a; INSIDE
	m = D|V*t + X|V (like the cylinder)
*/
void	hit_cone(t_vec3 d, t_object *packed_cone, \
	t_hit *hit, t_vec3 origin)
{
	t_qdt		q;
	t_cone		*cone;

	cone = (t_cone *)packed_cone->obj;
	q.k = 1 + pow(tanf(cone->angle), 2);
	q.disp = vec_subs(origin, cone->position);
	q.a = vec_dot(d, d) - q.k * pow(vec_dot(d, vec_norm(cone->direction)), 2);
	q.half_b = vec_dot(d, q.disp) - q.k * vec_dot(d, vec_norm(cone->direction)) * vec_dot(q.disp, vec_norm(cone->direction));
	q.c = vec_dot(q.disp, q.disp) - q.k * pow(vec_dot(q.disp, vec_norm(cone->direction)), 2);
	q.discriminant = pow(q.half_b, 2) - (q.a * q.c);
	if (q.discriminant < 0.00001)
	{
		hit->obj = NULL;
		hit->t = ERROR;
		return ;
	}
	q.t = (-q.half_b - sqrtf(q.discriminant)) / q.a;
	q.m = vec_dot(d, vec_norm(cone->direction)) * q.t + vec_dot(q.disp, vec_norm(cone->direction));
	q.origin = origin;
	q.d = d;
	hit_cone_norm(q, hit, cone, packed_cone);
}