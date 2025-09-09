/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaro-ro <mcaro-ro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 05:50:43 by mcaro-ro          #+#    #+#             */
/*   Updated: 2025/09/09 18:12:33 by mcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cube.h"
#include <sys/time.h>

static bool	can_move(t_config *config)
{
	struct timeval	tv;
	double			now;
	double			diff;

	gettimeofday(&tv, NULL);
	now = tv.tv_sec * 1000.0 + tv.tv_usec / 1000.0;
	diff = now - config->last_time_ms;
	if (diff >= 100.0)
	{
		config->last_time_ms = now;
		return (true);
	}
	return (false);
}

void	update_player_movement(t_config *config)
{
	float	cos_angle;
	float	sin_angle;

	cos_angle = cos(config->player_angle);
	sin_angle = sin(config->player_angle);
	if (config->player_move.up)
	{
		config->player_x += cos_angle * PLAYER_SPEED;
		config->player_y += sin_angle * PLAYER_SPEED;
	}
	if (config->player_move.down)
	{
		config->player_x -= cos_angle * PLAYER_SPEED;
		config->player_y -= sin_angle * PLAYER_SPEED;
	}
	if (config->player_move.left)
	{
		config->player_x += cos_angle * PLAYER_SPEED;
		config->player_y -= sin_angle * PLAYER_SPEED;
	}
	if (config->player_move.right)
	{
		config->player_x -= cos_angle * PLAYER_SPEED;
		config->player_y += sin_angle * PLAYER_SPEED;
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

// void	update_player_rotation_mouse(t_config *config, double delta_x)
// {
// 	if (config->player_angle < 0)
// 		config->player_angle += 2 * M_PI;
// 	if (config->player_angle > 2 * M_PI)
// 		config->player_angle -= 2 * M_PI;
// }
