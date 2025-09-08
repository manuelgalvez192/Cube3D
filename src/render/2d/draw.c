/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaro-ro <mcaro-ro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 01:21:53 by mcaro-ro          #+#    #+#             */
/*   Updated: 2025/09/08 07:43:19 by mcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../cube.h"
#include "../../../colors.h"

void	draw_fill_sq(int x, int y, int size, mlx_image_t *img)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			put_pixel_safe(img, x + j, y + i, COLOR_PLACE_HOLDER);
			j++;
		}
		i++;
	}
}

void	draw_square(int x, int y, int size, mlx_image_t *img)
{
	int	i;

	if (size <= 0)
		return ;
	i = 0;
	while (i < size)
	{
		put_pixel_safe(img, x + i, y, COLOR_BLACK);
		put_pixel_safe(img, x + i, y + size - 1, COLOR_BLACK);
		put_pixel_safe(img, x, y + i, COLOR_BLACK);
		put_pixel_safe(img, x + size - 1, y + i, COLOR_BLACK);
		i++;
	}
}

void	draw_minimap_border(int x, int y, t_minimap *minimap)
{
	int	i;
	int	j;

	i = 0;
	while (i < minimap->width)
	{
		put_pixel_safe(minimap->img, x + i, y,
			BORDER_COLOR);
		put_pixel_safe(minimap->img, x + i, y + minimap->height - 1,
			BORDER_COLOR);
		i++;
	}
	j = 0;
	while (j < minimap->height)
	{
		put_pixel_safe(minimap->img, x, y + j, BORDER_COLOR);
		put_pixel_safe(minimap->img, x + minimap->width - 1, y + j,
			BORDER_COLOR);
		j++;
	}
}

void	draw_map_on_image(t_config *config)
{
	int		i;
	int		j;
	size_t	len;

	i = 0;
	clear_image(config->minimap.img);
	while (i < config->map_rows)
	{
		len = ft_strlen(config->map[i]);
		j = 0;
		while (j < (int)len)
		{
			if (config->map[i][j] == '1')
			{
				draw_fill_sq(j * config->minimap.tile, i * config->minimap.tile,
					config->minimap.tile, config->minimap.img);
				draw_square(j * config->minimap.tile, i * config->minimap.tile,
					config->minimap.tile + 1, config->minimap.img);
			}
			j++;
		}
		i++;
	}
	draw_minimap_border(0, 0, &config->minimap);
}
