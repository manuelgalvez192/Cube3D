/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render3d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaro-ro <mcaro-ro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 03:33:05 by mcaro-ro          #+#    #+#             */
/*   Updated: 2025/09/09 23:18:58 by mcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../cube.h"
#include "../../../colors.h"
#include <math.h>

static double	cast_ray(t_config *config, float angle, bool *hit_vertical)
{
	float	rx;
	float	ry;
	float	lx;
	float	ly;
	int		steps;

	steps = 0;
	rx = config->player_x + PLAYER_CENTER_OFF;
	ry = config->player_y + PLAYER_CENTER_OFF;
	lx = rx;
	ly = ry;
	while (steps < RAY_MAX_STEPS && is_walkable(config, rx, ry))
	{
		lx = rx;
		ly = ry;
		rx += cosf(angle) * RAY_STEP;
		ry += sinf(angle) * RAY_STEP;
		steps++;
	}
	*hit_vertical = (fabsf(rx - lx) > fabsf(ry - ly));
	return (sqrtf((rx - (config->player_x + PLAYER_CENTER_OFF))
		* (rx - (config->player_x + PLAYER_CENTER_OFF))
		+ (ry - (config->player_y + PLAYER_CENTER_OFF))
		* (ry - (config->player_y + PLAYER_CENTER_OFF))));
}

int	get_column_height(float dist, uint32_t screen_height)
{
	if (dist < 0.1f)
		dist = 0.1f;
	if (dist > 10.0f)
		dist = 10.0f;
	return ((int)(screen_height / dist));
}

static void render_column(t_config *c, int x)
{
    float   angle;
    float   raw;
    float   dist;
    int     tex_x;
    bool    hit_vert;

    angle = c->player_angle - (FOV / 2.0f)
        + ((float)x / c->img->width) * FOV;
    raw = cast_ray(c, angle, &hit_vert);
    dist = raw * cosf(angle - c->player_angle);
    tex_x = get_wall_tex_x(c, raw, angle, hit_vert);
    draw_textured_column(c, x, get_column_height(dist, c->img->height), tex_x);
}


void	render3d(t_config *config)
{
	int		i;

	i = 0;
	while ((uint32_t)i < config->img->width)
	{
		render_column(config, i);
		i++;
	}
}
