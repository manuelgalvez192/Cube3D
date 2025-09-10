/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaro-ro <mcaro-ro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 01:23:14 by mcaro-ro          #+#    #+#             */
/*   Updated: 2025/09/10 20:17:45 by mcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static void	compute_minimap_max(t_config *config)
{
	int	win_w;
	int	win_h;
	int	max_w;
	int	max_h;

	win_w = (int)config->img->width;
	win_h = (int)config->img->height;
	max_w = (int)(win_w * MINIMAP_RATIO);
	max_h = (int)(win_h * MINIMAP_RATIO);
	config->minimap.width = max_w;
	config->minimap.height = max_h;
}

static void	compute_minimap_offset(t_config *config)
{
	int	win_w;

	win_w = (int)config->img->width;
	config->minimap.x_off = win_w - MINIMAP_MARGIN - config->minimap.width;
	config->minimap.y_off = MINIMAP_MARGIN;
}

static void	compute_minimap_tile(t_config *config)
{
	int	map_w;
	int	map_r;
	int	tile_w;
	int	tile_h;

	map_w = config->map_width;
	if (map_w < 1)
		map_w = 1;
	map_r = config->map_rows;
	if (map_r < 1)
		map_r = 1;
	tile_w = config->minimap.width / map_w;
	tile_h = config->minimap.height / map_r;
	if (tile_h < tile_w)
		config->minimap.tile = tile_h;
	else
		config->minimap.tile = tile_w;
	if (config->minimap.tile < 1)
		config->minimap.tile = 1;
}

static void	compute_minimap_dims(t_config *config)
{
	int	map_w;
	int	map_r;

	map_w = config->map_width;
	if (map_w < 1)
		map_w = 1;
	map_r = config->map_rows;
	if (map_r < 1)
		map_r = 1;
	config->minimap.width = config->minimap.tile * map_w;
	config->minimap.height = config->minimap.tile * map_r;
}

void	compute_minimap(t_config *config)
{
	compute_minimap_max(config);
	compute_minimap_tile(config);
	compute_minimap_dims(config);
	compute_minimap_offset(config);
}
