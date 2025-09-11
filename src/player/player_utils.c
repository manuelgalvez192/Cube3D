/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaro-ro <mcaro-ro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 06:00:04 by mcaro-ro          #+#    #+#             */
/*   Updated: 2025/09/10 21:11:21 by mcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include <math.h>
#include <sys/time.h>

double	get_initial_angle(char dir)
{
	if (dir == 'N')
		return (3 * M_PI / 2);
	if (dir == 'S')
		return (M_PI / 2);
	if (dir == 'E')
		return (0);
	if (dir == 'W')
		return (M_PI);
	return (0);
}

static bool	is_cell_walkable(t_config *config, int mx, int my)
{
	size_t	row_len;

	if (my < 0 || my >= config->map_rows)
		return (false);
	if (!config->map[my])
		return (false);
	row_len = ft_strlen(config->map[my]);
	if (mx < 0 || (size_t)mx >= row_len)
		return (false);
	return (config->map[my][mx] == '0');
}

bool	is_walkable(t_config *config, float x, float y)
{
	int	int_x;
	int	int_y;

	int_x = (int)floorf(x);
	int_y = (int)floorf(y);
	return (is_cell_walkable(config, int_x, int_y));
}

bool	is_walkable_radius(t_config *config, float x, float y)
{
	int		i;
	float	ang;
	float	sx;
	float	sy;

	if (PLAYER_RADIUS <= 0.0f)
		return (is_walkable(config,
				(x + PLAYER_CENTER_OFF),
				(y + PLAYER_CENTER_OFF)));
	i = 0;
	while (i <= 32)
	{
		ang = (float)i * (float)M_PI / 4.0f;
		sx = (x + PLAYER_CENTER_OFF) + cosf(ang) * PLAYER_RADIUS;
		sy = (y + PLAYER_CENTER_OFF) + sinf(ang) * PLAYER_RADIUS;
		if (!is_walkable(config, sx, sy))
			return (false);
		i++;
	}
	return (true);
}
