/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaro-ro <mcaro-ro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 06:00:04 by mcaro-ro          #+#    #+#             */
/*   Updated: 2025/09/09 06:59:58 by mcaro-ro         ###   ########.fr       */
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

int	is_walkable(t_config *config, double x, double y)
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

void	get_direction_x(double angle, int *dx)
{
	double	cos_a;

	cos_a = cos(angle);
	if (cos_a > 0.5)
		*dx = 1;
	else if (cos_a < -0.5)
		*dx = -1;
	else
		*dx = 0;
}

void	get_direction_y(double angle, int *dy)
{
	double	sin_a;

	sin_a = sin(angle);
	if (sin_a > 0.5)
		*dy = 1;
	else if (sin_a < -0.5)
		*dy = -1;
	else
		*dy = 0;
}

bool	can_move(double *last_time, double delay_ms)
{
	struct timeval	now;
	double			current;

	gettimeofday(&now, NULL);
	current = now.tv_sec * 1000.0 + now.tv_usec / 1000.0;
	if (current - *last_time >= delay_ms)
	{
		*last_time = current;
		return (true);
	}
	return (false);
}
