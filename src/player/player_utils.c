/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaro-ro <mcaro-ro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 06:00:04 by mcaro-ro          #+#    #+#             */
/*   Updated: 2025/09/09 10:59:07 by mcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cube.h"
#include <math.h>
#include <sys/time.h>

double	get_initial_angle(char dir)
{
	if (dir == 'N')
		return (M_PI / 2);
	if (dir == 'S')
		return (3 * M_PI / 2);
	if (dir == 'E')
		return (0);
	if (dir == 'W')
		return (M_PI);
	return (0);
}

bool	is_walkable(t_config *config, double x, double y)
{
	int	int_x;
	int	int_y;

	int_x = (int)x;
	int_y = (int)y;
	return ((int_y >= 0)
		&& (int_y < config->map_rows)
		&& (int_x >= 0)
		&& (config->map[int_y][int_x])
		&& (config->map[int_y][int_x] == '0'));
}

bool	is_walkable_radius(t_config *config, double x, double y)
{
	return (is_walkable(config, x - PLAYER_RADIUS, y - PLAYER_RADIUS)
		&& is_walkable(config, x + PLAYER_RADIUS, y - PLAYER_RADIUS)
		&& is_walkable(config, x - PLAYER_RADIUS, y + PLAYER_RADIUS)
		&& is_walkable(config, x + PLAYER_RADIUS, y + PLAYER_RADIUS));
}
