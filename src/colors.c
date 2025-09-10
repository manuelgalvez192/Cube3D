/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaro-ro <mcaro-ro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 08:42:57 by mcaro-ro          #+#    #+#             */
/*   Updated: 2025/09/10 20:18:17 by mcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

uint32_t	get_color_value(t_color color)
{
	uint32_t	result;
	uint8_t		r;
	uint8_t		g;
	uint8_t		b;

	r = (uint8_t)color.r;
	g = (uint8_t)color.g;
	b = (uint8_t)color.b;
	result = (r << 24) | (g << 16) | (b << 8) | 0xFF;
	return (result);
}
