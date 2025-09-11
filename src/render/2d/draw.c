/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaro-ro <mcaro-ro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 01:21:53 by mcaro-ro          #+#    #+#             */
/*   Updated: 2025/09/10 20:49:32 by mcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "colors.h"

static void	draw_cell(t_config *config, int i, int j)
{
	t_rect	rect;

	rect.x = j * config->minimap.tile;
	rect.y = i * config->minimap.tile;
	rect.size = config->minimap.tile;
	draw_fill_sq(rect, COLOR_MINIMAP, config->minimap.img);
	draw_square(rect, COLOR_MINIMAP_BORDER, config->minimap.img);
}

void	draw_minimap_border(uint32_t color, t_minimap *minimap)
{
	int		i;
	int		j;
	t_rect	rect;

	i = 0;
	rect.x = 0;
	rect.y = 0;
	rect.w = minimap->width;
	rect.h = minimap->height;
	while (i < minimap->width)
	{
		put_pixel_safe(minimap->img, rect.x + i, rect.y,
			color);
		put_pixel_safe(minimap->img, rect.x + i,
			rect.y + minimap->height - 1, color);
		i++;
	}
	j = 0;
	while (j < minimap->height)
	{
		put_pixel_safe(minimap->img, rect.x, rect.y + j, color);
		put_pixel_safe(minimap->img, rect.x + minimap->width - 1,
			rect.y + j, color);
		j++;
	}
}

void	draw_player_on_minimap(t_config *config)
{
	t_rect	rect;
	int		ts;

	ts = config->minimap.tile;
	rect.size = ts / 2;
	rect.x = config->player_x * ts + (ts - rect.size) / 2;
	rect.y = config->player_y * ts + (ts - rect.size) / 2;
	draw_fill_sq(rect, COLOR_MINIMAP_PLAYER, config->minimap.img);
}

void	draw_map_on_image(t_config *config)
{
	int		i;
	int		j;

	i = 0;
	clear_image(config->minimap.img);
	while (i < config->map_rows)
	{
		j = 0;
		while (config->map[i][j] && j < config->map_width)
		{
			if (config->map[i][j] == '1')
				draw_cell(config, i, j);
			j++;
		}
		i++;
	}
	draw_minimap_border(COLOR_MINIMAP_BORDER, &config->minimap);
	draw_player_on_minimap(config);
	draw_player_ray_cone(config);
}

void	draw_ray_minimap(t_config *config, float cos_angle, float sin_angle)
{
	float	ray_x;
	float	ray_y;
	int		pix_x;
	int		pix_y;

	ray_x = config->player_x + PLAYER_CENTER_OFF;
	ray_y = config->player_y + PLAYER_CENTER_OFF;
	while (!is_wall_cell(config, ray_x, ray_y)
		&& !(is_wall_cell(config, ray_x + 1, ray_y)
			&& is_wall_cell(config, ray_x, ray_y + 1)))
	{
		pix_x = (int)(ray_x * config->minimap.tile);
		pix_y = (int)(ray_y * config->minimap.tile);
		put_pixel_safe(config->minimap.img, pix_x, pix_y, COLOR_RAY);
		ray_x += cos_angle;
		ray_y += sin_angle;
	}
}
