/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaro-ro <mcaro-ro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 04:57:55 by mcaro-ro          #+#    #+#             */
/*   Updated: 2025/09/13 22:59:22 by mcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "paths.h"

void	put_pixel_safe(mlx_image_t *img, int x, int y, uint32_t color)
{
	int	w;
	int	h;

	w = (int)img->width;
	h = (int)img->height;
	if (x < 0 || y < 0 || x >= w || y >= h)
		return ;
	mlx_put_pixel(img, x, y, color);
}

void	clear_image(mlx_image_t *img)
{
	size_t	pixels;

	pixels = (size_t)img->width * img->height;
	ft_memset(img->pixels, 0, pixels * sizeof(uint32_t));
}

void	init_images(t_config *config)
{
	int	win_w;
	int	win_h;

	win_w = config->mlx->width;
	win_h = config->mlx->height;
	config->img = mlx_new_image(config->mlx, win_w, win_h);
	mlx_image_to_window(config->mlx, config->img, 0, 0);
	compute_minimap(config);
	config->minimap.img = mlx_new_image(config->mlx,
			config->minimap.width,
			config->minimap.height);
	mlx_image_to_window(config->mlx, config->minimap.img,
		config->minimap.x_off, config->minimap.y_off);
}

void	run_game(t_config *config)
{
	compute_map_dims(config);
	printf("Esta es la ruta del no: %s\n", config->no_texture);
	if (!mlx_load_png(config->no_texture) || !mlx_load_png(config->so_texture)
		|| !mlx_load_png(config->ea_texture) || !mlx_load_png(config->we_texture))
		free_mlx(config);
	config->texture_wall.nort = mlx_load_png(config->no_texture);
	config->texture_wall.south = mlx_load_png(config->so_texture);
	config->texture_wall.east = mlx_load_png(config->ea_texture);
	config->texture_wall.west = mlx_load_png(config->we_texture);
	ft_memset(&config->player_move, 0, sizeof(config->player_move));
	mlx_set_setting(MLX_MAXIMIZED, true);
	config->mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", true);
	mlx_set_cursor_mode(config->mlx, MLX_MOUSE_HIDDEN);
	init_images(config);
	config->minimap.visibility = true;
	mlx_key_hook(config->mlx, on_key, config);
	mlx_resize_hook(config->mlx, on_resize, config);
	mlx_loop_hook(config->mlx, render, config);
	mlx_loop(config->mlx);
	mlx_terminate(config->mlx);
}
