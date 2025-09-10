/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaro-ro <mcaro-ro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 03:45:16 by mcaro-ro          #+#    #+#             */
/*   Updated: 2025/09/10 17:25:45 by mcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cube.h"

static double	dda_init_delta(double dir)
{
	if (dir == 0.0)
		return (1e30);
	return (fabs(1.0 / dir));
}

static void	dda_init_step(t_raydda *dda)
{
	if (dda->dir_x < 0.0)
	{
		dda->step_x = -1;
		dda->side_x = (dda->pos_x - dda->map_x) * dda->delta_x;
	}
	else
	{
		dda->step_x = 1;
		dda->side_x = (dda->map_x + 1.0 - dda->pos_x) * dda->delta_x;
	}
	if (dda->dir_y < 0.0)
	{
		dda->step_y = -1;
		dda->side_y = (dda->pos_y - dda->map_y) * dda->delta_y;
	}
	else
	{
		dda->step_y = 1;
		dda->side_y = (dda->map_y + 1.0 - dda->pos_y) * dda->delta_y;
	}
}

void	dda_init_state(t_config *config, t_raydda *dda, double rx, double ry)
{
	dda->pos_x = config->player_x + PLAYER_CENTER_OFF;
	dda->pos_y = config->player_y + PLAYER_CENTER_OFF;
	dda->map_x = (int)dda->pos_x;
	dda->map_y = (int)dda->pos_y;
	dda->dir_x = rx;
	dda->dir_y = ry;
	dda->delta_x = dda_init_delta(dda->dir_x);
	dda->delta_y = dda_init_delta(dda->dir_y);
	dda_init_step(dda);
}

int	dda_step_cell(t_config *config, t_raydda *dda)
{
	if (fabs(dda->side_x - dda->side_y) < 1e-6)
	{
		if (is_wall_cell(config, dda->map_x + dda->step_x, dda->map_y)
			|| is_wall_cell(config, dda->map_x, dda->map_y + dda->step_y))
			return (1);
	}
	if (dda->side_x < dda->side_y)
	{
		dda->side_x += dda->delta_x;
		dda->map_x += dda->step_x;
		dda->side = 0;
	}
	else
	{
		dda->side_y += dda->delta_y;
		dda->map_y += dda->step_y;
		dda->side = 1;
	}
	return (0);
}

t_rayhit	dda_cast(t_config *config, double rx, double ry)
{
	t_raydda	dda;
	t_rayhit	hit;

	dda_init_state(config, &dda, rx, ry);
	while (true)
	{
		if (dda_step_cell(config, &dda))
			break ;
		if (is_wall_cell(config, dda.map_x, dda.map_y))
			break ;
	}
	hit_init(&hit, dda);
	return (hit);
}
