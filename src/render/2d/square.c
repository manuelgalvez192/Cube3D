/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaro-ro <mcaro-ro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 20:43:10 by mcaro-ro          #+#    #+#             */
/*   Updated: 2025/09/08 20:49:13 by mcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../cube.h"

void	draw_fill_sq(t_rect rect, uint32_t color, mlx_image_t *img)
{
	int	i;
	int	j;

	i = 0;
	while (i < rect.size)
	{
		j = 0;
		while (j < rect.size)
		{
			put_pixel_safe(img, rect.x + j, rect.y + i, color);
			j++;
		}
		i++;
	}
}

void	draw_square(t_rect rect, uint32_t color, mlx_image_t *img)
{
	int	i;

	if (rect.size <= 0)
		return ;
	i = 0;
	while (i < rect.size)
	{
		put_pixel_safe(img, rect.x + i, rect.y, color);
		put_pixel_safe(img, rect.x + i, rect.y + rect.size - 1, color);
		put_pixel_safe(img, rect.x, rect.y + i, color);
		put_pixel_safe(img, rect.x + rect.size - 1, rect.y + i, color);
		i++;
	}
}
