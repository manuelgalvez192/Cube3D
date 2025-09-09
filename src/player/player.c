/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaro-ro <mcaro-ro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 04:47:57 by mcaro-ro          #+#    #+#             */
/*   Updated: 2025/09/09 19:15:26 by mcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cube.h"
#include "../../colors.h"
#include <math.h>

static int	is_blocked_cell(t_config *config, double x, double y)
{
	int	int_x;
	int	int_y;

	int_x = (int)x;
	int_y = (int)y;
	return (int_y < 0 || int_y >= config->map_rows
		|| int_x < 0 || !config->map[int_y][int_x]
		|| config->map[int_y][int_x] != '0');
}

void	draw_ray_angle(t_config *config, double angle)
{
	double	rx;
	double	ry;
	int		i;

	i = 0;
	rx = config->player_x + 0.5;
	ry = config->player_y + 0.5;
	while ((uint32_t)i < config->img->width)
	{
		if (is_blocked_cell(config, rx, ry))
			break ;
		put_pixel_safe(config->minimap.img,
			(int)(rx * config->minimap.tile),
			(int)(ry * config->minimap.tile),
			COLOR_RAY);
		rx += cos(angle) * RAY_STEP;
		ry += sin(angle) * RAY_STEP;
	}
}

void	draw_player_ray_cone(t_config *config)
{
	int		i;
	double	angle;
	double	start_a;
	double	end_a;

	i = 0;
	start_a = config->player_angle - (FOV / 2);
	end_a = config->player_angle + (FOV / 2);
	while ((uint32_t)i < config->img->width)
	{
		angle = start_a + ((double)i / config->img->width) * (end_a - start_a);
		draw_ray_angle(config, angle);
		i++;
	}
}
