/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaro-ro <mcaro-ro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 06:23:33 by mcaro-ro          #+#    #+#             */
/*   Updated: 2025/09/13 23:25:39 by mcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	on_resize(int new_w, int new_h, void *param)
{
	t_config	*config;

	config = param;
	if (new_w < 1)
		new_w = 1;
	if (new_h < 1)
		new_h = 1;
	mlx_resize_image(config->img, new_w, new_h);
	compute_minimap(config);
	mlx_delete_image(config->mlx, config->minimap.img);
	config->minimap.img = mlx_new_image(config->mlx,
			config->minimap.width,
			config->minimap.height);
	mlx_image_to_window(config->mlx, config->minimap.img,
		config->minimap.x_off, config->minimap.y_off);
}

static void	key_press(mlx_key_data_t keydata, t_config *config)
{
	if (keydata.key == MLX_KEY_W)
		config->player_move.up = true;
	if (keydata.key == MLX_KEY_S)
		config->player_move.down = true;
	if (keydata.key == MLX_KEY_A)
		config->player_move.left = true;
	if (keydata.key == MLX_KEY_D)
		config->player_move.right = true;
	if (keydata.key == MLX_KEY_LEFT)
		config->player_move.rotate_left = true;
	if (keydata.key == MLX_KEY_RIGHT)
		config->player_move.rotate_right = true;
}

static void	key_release(mlx_key_data_t keydata, t_config *config)
{
	if (keydata.key == MLX_KEY_W)
		config->player_move.up = false;
	if (keydata.key == MLX_KEY_S)
		config->player_move.down = false;
	if (keydata.key == MLX_KEY_A)
		config->player_move.left = false;
	if (keydata.key == MLX_KEY_D)
		config->player_move.right = false;
	if (keydata.key == MLX_KEY_LEFT)
		config->player_move.rotate_left = false;
	if (keydata.key == MLX_KEY_RIGHT)
		config->player_move.rotate_right = false;
}

void	on_key(mlx_key_data_t keydata, void *param)
{
	t_config	*config;

	config = param;
	if (keydata.key == MLX_KEY_ESCAPE)
	{
		// mlx_close_window(config->mlx);
		free_mlx(config);
	}
	if (keydata.key == MLX_KEY_M && keydata.action == MLX_PRESS)
		config->minimap.visibility = !config->minimap.visibility;
	if (keydata.action == MLX_PRESS)
		key_press(keydata, config);
	if (keydata.action == MLX_RELEASE)
		key_release(keydata, config);
}
