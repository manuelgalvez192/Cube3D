/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaro-ro <mcaro-ro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 15:52:10 by mcaro-ro          #+#    #+#             */
/*   Updated: 2025/09/10 20:18:06 by mcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "colors.h"

int	is_wall_cell(t_config *config, int mx, int my)
{
	if (my < 0 || my >= config->map_rows
		|| mx < 0 || mx >= config->map_width)
		return (1);
	return (config->map[my][mx] == '1');
}

void	hit_init(t_rayhit *hit, t_raydda dda)
{
	hit->side = dda.side;
	hit->map_x = dda.map_x;
	hit->map_y = dda.map_y;
	if (dda.side == 0)
	{
		hit->perp_dist = dda.side_x - dda.delta_x;
		hit->wall_x = dda.pos_y + hit->perp_dist * dda.dir_y;
	}
	else
	{
		hit->perp_dist = dda.side_y - dda.delta_y;
		hit->wall_x = dda.pos_x + hit->perp_dist * dda.dir_x;
	}
	hit->wall_x -= floor(hit->wall_x);
	hit->ray_x = dda.dir_x;
	hit->ray_y = dda.dir_y;
}
