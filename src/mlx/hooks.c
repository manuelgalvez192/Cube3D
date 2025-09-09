/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaro-ro <mcaro-ro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 06:23:33 by mcaro-ro          #+#    #+#             */
/*   Updated: 2025/09/09 07:24:22 by mcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cube.h"

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

void	on_key(mlx_key_data_t keydata, void *param)
{
	t_config	*config;
	bool		pressed;

	config = param;
	pressed = keydata.action != MLX_RELEASE;
	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(config->mlx);
	if (keydata.key == MLX_KEY_M && keydata.action == MLX_PRESS)
		config->minimap.visibility = !config->minimap.visibility;
	if (keydata.key == MLX_KEY_W)
		config->player_move.up = pressed;
	if (keydata.key == MLX_KEY_S)
		config->player_move.down = pressed;
	if (keydata.key == MLX_KEY_A)
		config->player_move.left = pressed;
	if (keydata.key == MLX_KEY_D)
		config->player_move.right = pressed;
	if (keydata.key == MLX_KEY_LEFT)
		config->player_move.rotate_left = pressed;
	if (keydata.key == MLX_KEY_RIGHT)
		config->player_move.rotate_right = pressed;
}
