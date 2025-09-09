/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaro-ro <mcaro-ro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 05:50:43 by mcaro-ro          #+#    #+#             */
/*   Updated: 2025/09/09 11:11:51 by mcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cube.h"
#include <sys/time.h>

static bool can_move(t_config *config)
{
	struct timeval	tv;
	double			now;
	double			diff;

	gettimeofday(&tv, NULL);
	now = tv.tv_sec * 1000.0 + tv.tv_usec / 1000.0;
	diff =  now - config->last_time_ms;
	if (diff >= 100.0)
	{
		config->last_time_ms = now;
		return (true);
	}
	return (false);
}

static void	move_in_direction(t_config *config, double dx, double  dy)
{
	double	new_x;
	double	new_y;

	new_x = config->player_x + dx;
	new_y = config->player_y + dy;
	if (is_walkable_radius(config, new_x, config->player_y))
		config->player_x = new_x;
	if (is_walkable_radius(config, config->player_x, new_y))
		config->player_y = new_y;
}

void	update_player_movement(t_config *config)
{
	if (!can_move(config))
		return ;
	if (config->player_move.up)
		move_in_direction(config, 0, -1);
	if (config->player_move.down)
		move_in_direction(config, 0, 1);
	if (config->player_move.left)
		move_in_direction(config, -1, 0);
	if (config->player_move.right)
		move_in_direction(config, 1, 0);
}
