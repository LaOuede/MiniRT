/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   damier.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gle-roux <gle-roux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 14:03:29 by gle-roux          #+#    #+#             */
/*   Updated: 2023/09/19 14:04:46 by gle-roux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	load_damier(void)
{
	t_minirt	*minirt;

	minirt = get_minirt();
	minirt->material[DAMIER].id = DAMIER;
	minirt->material[DAMIER].texture = \
	mlx_load_png("textures_png/damier/damier.png");
	minirt->material[DAMIER].norm_map = NULL;
	minirt->material[DAMIER].shine = 10000;
	minirt->material[DAMIER].reflexion = 0.1;
	minirt->material[DAMIER].specular_factor = 1;
}
