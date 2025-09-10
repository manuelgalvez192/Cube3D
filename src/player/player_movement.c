/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaro-ro <mcaro-ro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 05:50:43 by mcaro-ro          #+#    #+#             */
/*   Updated: 2025/09/10 20:20:32 by mcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include <sys/time.h>

double	get_delta_time(void)
{
	static struct timeval	last = {0};
	struct timeval			now;
	double					delta_time;

	gettimeofday(&now, NULL);
	if (last.tv_sec == 0 && last.tv_usec == 0)
		last = now;
	delta_time = (now.tv_sec - last.tv_sec)
		+ (now.tv_usec - last.tv_usec) / 1000000.0;
	last = now;
	return (delta_time);
}

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

void	update_player_movement(t_config *config, double delta_time)
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
		dx = (dx / len) * PLAYER_SPEED * delta_time;
		dy = (dy / len) * PLAYER_SPEED * delta_time;
		if (is_walkable_radius(config,
				config->player_x + dx * PLAYER_SPEED,
				config->player_y))
			config->player_x += dx;
		if (is_walkable_radius(config,
				config->player_x,
				config->player_y + dy * PLAYER_SPEED))
			config->player_y += dy;
	}
}

void	update_player_rotation_keys(t_config *config, double delta_time)
{
	if (config->player_move.rotate_left)
		config->player_angle -= PLAYER_ROT_SPEED * delta_time;
	if (config->player_move.rotate_right)
		config->player_angle += PLAYER_ROT_SPEED * delta_time;
	if (config->player_angle > 2 * M_PI)
		config->player_angle -= 2 * M_PI;
	if (config->player_angle < 0)
		config->player_angle += 2 * M_PI;
}
