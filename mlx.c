/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaro-ro <mcaro-ro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 04:57:55 by mcaro-ro          #+#    #+#             */
/*   Updated: 2025/09/08 04:39:13 by mcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

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

void clear_image(mlx_image_t *img)
{
	size_t pixels;
	
	pixels = (size_t)img->width * img->height;
	ft_memset(img->pixels, 0, pixels * sizeof(uint32_t));
}

void on_resize(int new_w, int new_h, void *param)
{
	t_config	*config;

	config = param;
	if (new_w < 1)
		new_w = 1;
	if (new_h < 1)
		new_h = 1;
	mlx_resize_image(config->img3d, new_w, new_h);
	compute_minimap(config);
	mlx_delete_image(config->mlx, config->minimap.img2d);
	config->minimap.img2d = mlx_new_image(config->mlx, config->minimap.width, config->minimap.height);
	mlx_image_to_window(config->mlx, config->minimap.img2d,
		config->minimap.x_off, config->minimap.y_off);
}

void	init_images(t_config *config)
{
	int	win_w;
	int	win_h;

	win_w = config->mlx->width;
	win_h = config->mlx->height;
	config->img3d = mlx_new_image(config->mlx, win_w, win_h);
	mlx_image_to_window(config->mlx, config->img3d, 0, 0);
	compute_minimap(config);
	config->minimap.img2d = mlx_new_image(config->mlx, config->minimap.width, config->minimap.height);
	mlx_image_to_window(config->mlx, config->minimap.img2d,
		config->minimap.x_off, config->minimap.y_off);
}

void	run_game(t_config *config)
{
	compute_map_dims(config);
	mlx_set_setting(MLX_MAXIMIZED, true);
	config->mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", true);
	init_images(config);
	mlx_resize_hook(config->mlx, on_resize, config);
	mlx_loop_hook(config->mlx, render, config);
	mlx_loop(config->mlx);
	mlx_terminate(config->mlx);
}
