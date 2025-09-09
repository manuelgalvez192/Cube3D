/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaro-ro <mcaro-ro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 05:28:39 by mcaro-ro          #+#    #+#             */
/*   Updated: 2025/09/09 19:46:19 by mcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	on_mouse_move(t_config *config)
{
	static int32_t	last_x;
	int32_t			x;
	int32_t			y;

	last_x = -1;
	mlx_get_mouse_pos(config->mlx, &x, &y);
	if (last_x == -1)
	{
		last_x = x;
		return ;
	}
	update_player_rotation_mouse(config);
	last_x = x;
}

void	update_player_rotation_mouse(t_config *config)
{
	if (config->player_angle < 0)
		config->player_angle += 2 * M_PI;
	if (config->player_angle > 2 * M_PI)
		config->player_angle -= 2 * M_PI;
}
