/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaro-ro <mcaro-ro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 02:05:00 by mcaro-ro          #+#    #+#             */
/*   Updated: 2025/09/08 03:51:01 by mcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	render(void *param)
{
	t_config	*config;

	config = param;
	clear_image(config->img3d);
	render3d(config);
	compute_minimap(config);
	clear_image(config->minimap.img2d);
	draw_map_on_image(config);
}
