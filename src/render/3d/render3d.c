/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render3d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaro-ro <mcaro-ro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 03:33:05 by mcaro-ro          #+#    #+#             */
/*   Updated: 2025/09/10 20:17:55 by mcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include <math.h>

static void	draw_textured_column(t_config *config, t_col_data *col)
{
	int	y;
	int	start;
	int	end;

	start = (int)(config->img->height / 2) - (col->height / 2);
	end = start + col->height;
	y = 0;
	while ((uint32_t)y < config->img->height)
	{
		if (y >= start && y < end)
		{
			put_pixel_safe(config->img, col->x, y,
				get_texture_pixel(col->tex, col->tex_x,
					((y - start) * col->tex->height) / col->height));
		}
		if (y < start)
			put_pixel_safe(config->img, col->x, y,
				get_color_value(config->ceiling));
		else if (y >= end)
			put_pixel_safe(config->img, col->x, y,
				get_color_value(config->floor));
		y++;
	}
}

static int	get_column_height(double prep, uint32_t screen_height)
{
	if (prep < OFFSET_EPSILON)
		prep = OFFSET_EPSILON;
	return ((int)(screen_height / prep));
}

void	render_column(t_config *config, int x)
{
	double		angle;
	t_rayhit	hit;
	t_col_data	col;

	angle = config->player_angle - (FOV / 2.0)
		+ ((double)x / (double)config->img->width) * FOV;
	hit = dda_cast(config, cos(angle), sin(angle));
	col.height = get_column_height(hit.perp_dist, config->img->height);
	col.x = x;
	col.tex = get_wall_texture(config, side_from_hit(&hit));
	col.tex_x = tex_x_from_hit(&hit, col.tex);
	draw_textured_column(config, &col);
}

void	render3d(t_config *config)
{
	int		i;

	i = 0;
	while ((uint32_t)i < config->img->width)
	{
		render_column(config, i);
		i++;
	}
}
