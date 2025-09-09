/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render3d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaro-ro <mcaro-ro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 03:33:05 by mcaro-ro          #+#    #+#             */
/*   Updated: 2025/09/09 19:27:16 by mcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../cube.h"
#include "../../../colors.h"
#include <math.h>

static double	cast_ray(t_config *config, double angle)
{
	double	ray_x;
	double	ray_y;
	int		steps;
	bool	blocked;

	steps = 0;
	blocked = false;
	ray_x = config->player_x + 0.5;
	ray_y = config->player_y + 0.5;
	while (steps < RAY_MAX_STEPS && !blocked)
	{
		ray_x += cos(angle) * RAY_STEP;
		ray_y += sin(angle) * RAY_STEP;
		blocked = !is_walkable(config, ray_x, ray_y);
		steps++;
	}
	return (sqrt(pow(ray_x - (config->player_x + 0.5), 2)
			+ pow(ray_y - (config->player_y + 0.5), 2)));
}

int	get_column_height(double dist, uint32_t screen_height)
{
	if (dist < 0.1f)
		dist = 0.1f;
	if (dist > 10.0f)
		dist = 10.0f;
	return ((int)(screen_height / dist));
}

static uint32_t	get_wall_color(double dist)
{
	uint32_t	base;
	uint8_t		shade;

	base = COLOR_WALL;
	if (dist > 1.0)
	{
		shade = (uint8_t)(255 / dist);
		return ((shade << 24) | (shade << 16) | (shade << 8) | 0xFF);
	}
	return (base);
}

static void	draw_column(t_config *config, int x, int height, double dist)
{
	int			y;
	int			start;
	int			end;
	uint32_t	color;

	y = 0;
	start = (int)(config->img->height / 2) - (height / 2);
	end = start + height;
	while ((uint32_t)y < config->img->height)
	{
		if (y < start)
			put_pixel_safe(config->img, x, y, get_color_value(config->ceiling));
		else if (y >= end)
			put_pixel_safe(config->img, x, y, get_color_value(config->floor));
		else
		{
			color = get_wall_color(dist);
			put_pixel_safe(config->img, x, start + y, color);
		}
		y++;
	}
}

void	render3d(t_config *config)
{
	int		i;
	double	angle;
	double	dist;
	int		col_x;

	i = 0;
	while ((uint32_t)i < config->img->width)
	{
		angle = config->player_angle - (FOV / 2)
			+ ((double)i / config->img->width) * FOV;
		dist = cast_ray(config, angle);
		dist *= cos(angle - config->player_angle);
		col_x = i;
		draw_column(config, col_x,
			get_column_height(dist, config->img->height), dist);
		i++;
	}
}
