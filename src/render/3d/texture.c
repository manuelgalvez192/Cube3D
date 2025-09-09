/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaro-ro <mcaro-ro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 20:50:48 by mcaro-ro          #+#    #+#             */
/*   Updated: 2025/09/09 23:37:22 by mcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../cube.h"
#include <math.h>

int	get_wall_tex_x(t_config *config, float raw_dist, float angle, bool hit_vertical)
{
	float	hit_x;
	float	hit_y;
	float	off_set;
	int		tex_x;

	raw_dist -= (RAY_STEP * 0.5f);
	if (raw_dist < 0.0f)
		raw_dist = 0.0f;
	hit_x = config->player_x + PLAYER_CENTER_OFF + cosf(angle) * raw_dist;
	hit_y = config->player_y + PLAYER_CENTER_OFF + sinf(angle) * raw_dist;
	if (hit_vertical)
		off_set = fmod(hit_y + OFFSET_EPSILON, 1.0f);
	else
		off_set = fmod(hit_x + OFFSET_EPSILON, 1.0f);
	tex_x = (int)(off_set * config->texture.wall->width);
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= (int)config->texture.wall->width)
		tex_x = config->texture.wall->width - 1;
	return (tex_x);
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

void	draw_textured_column(t_config *config, int x, int height, int tex_x)
{
	int	y;
	int	start;
	int	end;
	int	tex_y;
	int	color;

	start = (int)(config->img->height / 2) - (height / 2);
	end = start + height;
	y = 0;
	while ((uint32_t)y < config->img->height)
	{
		if (y < start)
			put_pixel_safe(config->img, x, y, get_color_value(config->ceiling));
		else if (y >= end)
			put_pixel_safe(config->img, x, y, get_color_value(config->floor));
		else
		{
			tex_y = ((y - start) * config->texture.wall->height) / height;
			color = get_texture_pixel(config->texture.wall, tex_x, tex_y);
			put_pixel_safe(config->img, x, y, color);
		}
		y++;
	}
}
