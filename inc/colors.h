/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaro-ro <mcaro-ro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 07:17:43 by mcaro-ro          #+#    #+#             */
/*   Updated: 2025/09/23 17:34:59 by mcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLORS_H
# define COLORS_H

# define COLOR_PLACE_HOLDER		0xF0F0F00F

# define COLOR_MINIMAP			0x0F000FFF
# define COLOR_MINIMAP_PLAYER	0x00FF00FF
# define COLOR_MINIMAP_BORDER	0xFFFFFFFF

# define COLOR_RAY				0xFFFF00FF

# define COLOR_WALL				0x0000FFFF

# define COLOR_TRANSPARENT		0x0000000F
# define COLOR_WHITE			0xFFFFFFFF
# define COLOR_BLACK			0x000000FF
# define COLOR_BLUE				0x0000FFFF
# define COLOR_YELLOW			0xFFFF00FF

/**
 *  ____  _                  _            
 * / ___|| |_ __ _ _ __   __| | __ _ _ __ 
 * \___ \| __/ _` | '_ \ / _` |/ _` | '__|
 *  ___) | || (_| | | | | (_| | (_| | |   
 * |____/ \__\__,_|_| |_|\__,_|\__,_|_|   
 */

# define COLOR_MSG_BLACK   			"\001\033[30m\002"
# define COLOR_MSG_WHITE   			"\001\033[37m\002"
# define COLOR_MSG_RED     			"\001\033[31m\002"
# define COLOR_MSG_GREEN   			"\001\033[32m\002"
# define COLOR_MSG_YELLOW  			"\001\033[33m\002"
# define COLOR_MSG_BLUE    			"\001\033[34m\002"
# define COLOR_MSG_MAGENTA 			"\001\033[35m\002"
# define COLOR_MSG_CYAN    			"\001\033[36m\002"
# define COLOR_MSG_GREY    			"\001\033[90m\002"
# define COLOR_MSG_RESET			"\001\033[0m\002"

#endif
