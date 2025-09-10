/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaro-ro <mcaro-ro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 20:50:48 by mcaro-ro          #+#    #+#             */
/*   Updated: 2025/09/10 20:17:59 by mcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

t_wall_side	side_from_hit(const t_rayhit *hit)
{
	if (hit->side == 0)
	{
		if (hit->ray_x > 0.0)
			return (EAST);
		return (WEST);
	}
	if (hit->ray_y > 0.0)
		return (SOUTH);
	return (NORTH);
}

int	tex_x_from_hit(const t_rayhit *hit, const mlx_texture_t *tex)
{
	int	tx;

	tx = (int)(hit->wall_x * (double)tex->width);
	if (hit->side == 0 && hit->ray_x > 0.0)
		tx = (int)tex->width - tx - 1;
	if (hit->side == 1 && hit->ray_y < 0.0)
		tx = (int)tex->width - tx - 1;
	if (tx < 0)
		tx = 0;
	if (tx >= (int)tex->width)
		tx = (int)tex->width - 1;
	return (tx);
}

mlx_texture_t	*get_wall_texture(t_config *config, t_wall_side side)
{
	if (side == NORTH)
		return (config->texture_wall.nort);
	if (side == SOUTH)
		return (config->texture_wall.south);
	if (side == EAST)
		return (config->texture_wall.east);
	return (config->texture_wall.west);
}

int	get_texture_pixel(mlx_texture_t *tex, int x, int y)
{
	int		i;
	uint8_t	*p;

	if (x < 0 || x >= (int)tex->width || y < 0 || y >= (int)tex->height)
		return (0);
	i = (y * tex->width + x) * 4;
	p = &tex->pixels[i];
	return ((p[0] << 24) | (p[1] << 16) | (p[2] << 8) | p[3]);
}
