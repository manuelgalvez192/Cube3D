/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaro-ro <mcaro-ro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 01:21:53 by mcaro-ro          #+#    #+#             */
/*   Updated: 2025/09/08 04:52:44 by mcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cube.h"

void	draw_square(int x, int y, int size, uint32_t color, mlx_image_t *img)
{
	int	i;
	int j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size) 
		{
			put_pixel_safe(img, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

void	draw_square_border(int x, int y, int size, uint32_t color, mlx_image_t *img)
{
	int	i;

	if (size <= 0)
		return ;
	i = 0;
	while (i < size)
	{
		put_pixel_safe(img, x + i, y, color);
		put_pixel_safe(img, x + i, y + size - 1, color);
		put_pixel_safe(img, x, y + i, color);
		put_pixel_safe(img, x + size - 1, y + i, color);
		i++;
	}
}

void	draw_rectangle_border(int x, int y, int w, int h, mlx_image_t *img)
{
	int	i;
	int	j;

	i = 0;
	while (i < w)
	{
		put_pixel_safe(img, x + i, y, BORDER_COLOR);
		put_pixel_safe(img, x + i, y + h - 1, BORDER_COLOR);
		i++;
	}
	j = 0;
	while (j < h)
	{
		put_pixel_safe(img, x, y + j, BORDER_COLOR);
		put_pixel_safe(img, x + w - 1, y + j, BORDER_COLOR);
		j++;
	}
}

void	draw_map_on_image(t_config *config)
{
	int		i;
	int		j;
	size_t	len;
	int		ts;

	i = 0;
	ts = config->minimap.tile;
	clear_image(config->minimap.img2d);
	while (i < config->map_rows)
	{
		len = ft_strlen(config->map[i]);
		j = 0;
		while (j < (int)len)
		{
			if (config->map[i][j] == '1')
			{
				draw_square(j * ts, i * ts, ts, 0xF0F0FF0F, config->minimap.img2d);
				draw_square_border(j * ts, i * ts, ts, 0x00000000, config->minimap.img2d);
			}
			j++;
		}
		i++;
	}
	draw_rectangle_border(0, 0, config->minimap.width, config->minimap.height, config->minimap.img2d);
}
