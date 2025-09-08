/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaro-ro <mcaro-ro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 06:23:33 by mcaro-ro          #+#    #+#             */
/*   Updated: 2025/09/08 07:25:15 by mcaro-ro         ###   ########.fr       */
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
	mlx_resize_image(config->img3d, new_w, new_h);
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

	config = param;
	if (keydata.action != MLX_PRESS)
		return ;
	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(config->mlx);
	if (keydata.key == MLX_KEY_M)
		config->minimap.visibility = !config->minimap.visibility;
}
