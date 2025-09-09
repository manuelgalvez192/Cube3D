/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaro-ro <mcaro-ro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 05:50:43 by mcaro-ro          #+#    #+#             */
/*   Updated: 2025/09/09 20:28:21 by mcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cube.h"
#include <sys/time.h>
#include <math.h>

static void	accumulate_direction(float *dx, float *dy, t_config *config)
{
	if (config->player_move.up)
	{
		*dx += cos(config->player_angle);
		*dy += sin(config->player_angle);
	}
	if (config->player_move.down)
	{
		*dx -= cos(config->player_angle);
		*dy -= sin(config->player_angle);
	}
	if (config->player_move.left)
	{
		*dx += sin(config->player_angle);
		*dy -= cos(config->player_angle);
	}
	if (config->player_move.right)
	{
		*dx -= sin(config->player_angle);
		*dy += cos(config->player_angle);
	}
}

void	update_player_movement(t_config *config)
{
	float	dx;
	float	dy;
	float	len;

	dx = 0.0f;
	dy = 0.0f;
	accumulate_direction(&dx, &dy, config);
	len = sqrt(dx * dx + dy * dy);
	if (len != 0)
	{
		dx /= len;
		dy /= len;
		if (is_walkable_radius(config,
			config->player_x + dx * PLAYER_SPEED,
			config->player_y))
			config->player_x += dx * PLAYER_SPEED;
		if (is_walkable_radius(config,
			config->player_x,
			config->player_y + dy * PLAYER_SPEED))
			config->player_y += dy * PLAYER_SPEED;
	}
}

void	update_player_rotation_keys(t_config *config)
{
	if (config->player_move.rotate_left)
		config->player_angle -= ROT_SPEED;
	if (config->player_move.rotate_right)
		config->player_angle += ROT_SPEED;
	if (config->player_angle > 2 * M_PI)
		config->player_angle = 0;
	if (config->player_angle < 0)
		config->player_angle = 2 * M_PI;
}
