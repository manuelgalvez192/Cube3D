/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaro-ro <mcaro-ro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 06:53:11 by mcaro-ro          #+#    #+#             */
/*   Updated: 2025/09/23 17:30:44 by mcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRINGS_H
# define STRINGS_H

# define MSG_ERR_MISSING_TEXTURE "Error\tTextura no encontrada\n"
# define MSG_ERR_INVALID_LINE	"Error\tMapa contiene línea inválida\n"
# define MSG_ERR_INVALID_CHAR	"Error\tMapa contiene carácter inválido\n"
# define MSG_ERR_ROW_COUNT_DONT_MATCH	"Error\tConteo de filas no coincide\n"
# define MSG_ERR_OPENING_FILE	"Error\tNo se pudo reabrir el archivo\n"
# define MSG_ERR_MALLOC_MAP		"Error\tFallo malloc mapa\n"
# define MSG_ERR_INVALID_MAP	"Error\tMapa inválido\n"
# define MSG_ERR_MEMORY_ALOCATION	"Error\tFallo al asignar memoria\n"
# define MSG_ERR_TEXTURE_IDENTIFIER	"Error\tIdentificador de textura inválido\n"
# define MSG_ERR_TEXTURE_FORMAT	"Error\t\
	Formato inválido: espacio requerido después del identificador de textura\n"
# define MSG_ERR_TEXTURE_PATH	"Error\tFalta path en textura\n"
# define MSG_ERR_RGB			"Error\tRGB invalido\n"
# define MSG_ERR_RGB_OUT_OF_RANGE	"Error\tValor RGB fuera de rango\n"
# define MSG_ERR_FORMAT_SPACE_BEFORE	"Error\t\
	Formato inválido: espacio requerido después de "
# define MSG_ERR_PARSE_HEADER_OR_MAP	"Error\t\
	Fallo al parsear el header o mapa\n"
# define MSG_ERR_MAP_NOT_FOUND		"Error\tMapa no encontrado\n"
# define MSG_ERR_MAP_NOT_STARTING_POINT	"Error\t\
	El mapa debe tener exactamente un punto de inicio\n"

#endif
