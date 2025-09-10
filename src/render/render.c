/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaro-ro <mcaro-ro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 02:05:00 by mcaro-ro          #+#    #+#             */
/*   Updated: 2025/09/10 20:18:12 by mcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	render(void *param)
{
	t_config		*config;
	double			delta_time;

	config = param;
	// on_mouse_move(config);
	delta_time = get_delta_time();
	update_player_rotation_keys(config, delta_time);
	update_player_movement(config, delta_time);
	clear_image(config->img);
	render3d(config);
	if (config->minimap.visibility == true)
	{
		compute_minimap(config);
		clear_image(config->minimap.img);
		draw_map_on_image(config);
	}
	else
		clear_image(config->minimap.img);
}
