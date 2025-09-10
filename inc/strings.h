/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaro-ro <mcaro-ro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 06:53:11 by mcaro-ro          #+#    #+#             */
/*   Updated: 2025/09/09 07:47:33 by mcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRINGS_H
# define STRINGS_H

# define MSG_ERR_INVALID_LINE	"Error\nMapa contiene línea inválida\n"
# define MSG_ERR_INVALID_CHAR	"Error\nMapa contiene carácter inválido\n"
# define MSG_ERR_ROW_COUNT_DONT_MATCH	"Error\nConteo de filas no coincide\n"
# define MSG_ERR_OPENING_FILE	"Error\nNo se pudo reabrir el archivo\n"
# define MSG_ERR_MALLOC_MAP		"Error\nFallo malloc mapa\n"
# define MSG_ERR_INVALID_MAP	"Error\nMapa inválido\n"
# define MSG_ERR_MEMORY_ALOCATION	"Error\nFallo al asignar memoria\n"
# define MSG_ERR_TEXTURE_IDENTIFIER	"Error\nIdentificador de textura inválido\n"
# define MSG_ERR_TEXTURE_FORMAT	"Error\n\
	Formato inválido: espacio requerido después del identificador de textura\n"
# define MSG_ERR_TEXTURE_PATH	"Error\nFalta path en textura\n"
# define MSG_ERR_RGB			"Error\nRGB invalido\n"
# define MSG_ERR_RGB_OUT_OF_RANGE	"Error\nValor RGB fuera de rango\n"
# define MSG_ERR_FORMAT_SPACE_BEFORE	"Error\n\
	Formato inválido: espacio requerido después de "
# define MSG_ERR_PARSE_HEADER_OR_MAP	"Error\n\
	Fallo al parsear el header o mapa\n"
# define MSG_ERR_MAP_NOT_FOUND		"Error\nMapa no encontrado\n"
# define MSG_ERR_MAP_NOT_STARTING_POINT	"Error\n\
	El mapa debe tener exactamente un punto de inicio\n"

#endif
