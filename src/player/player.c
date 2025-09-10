/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaro-ro <mcaro-ro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 04:47:57 by mcaro-ro          #+#    #+#             */
/*   Updated: 2025/09/10 20:17:27 by mcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "colors.h"
#include <math.h>

void	draw_player_ray_cone(t_config *config)
{
	int		i;
	double	angle;
	double	start_a;
	double	end_a;

	i = 0;
	start_a = config->player_angle - (FOV / 2.0);
	end_a = config->player_angle + (FOV / 2.0);
	while ((uint32_t)i < config->img->width)
	{
		angle = start_a + ((double)i / (double)config->img->width)
			* (end_a - start_a);
		draw_ray_minimap(config, cos(angle), sin(angle));
		i++;
	}
}
