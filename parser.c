/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalvez- <mgalvez-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 00:05:59 by mgalvez-          #+#    #+#             */
/*   Updated: 2025/08/30 03:20:56 by mgalvez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int parse_header(int fd, t_config *config, char **map_line)
{
    char *line;
    char *trimmed;
    int ret;

    while ((line = get_next_line(fd)))
    {
        trimmed = ft_strtrim(line, " \t\n");
        free(line);
        if (!trimmed)
            return -1;

        if (*trimmed == '\0') // línea vacía
        {
            free(trimmed);
            continue;
        }

        ret = parse_texture_line(trimmed, config);
        if (ret == 1)
        {
            free(trimmed);
            continue; // línea procesada como textura
        }
        else if (ret == -1)
        {
            free(trimmed);
            return -1; // error real
        }

        ret = parse_color_line(trimmed, config);
        if (ret == 1)
        {
            free(trimmed);
            continue; // línea procesada como color
        }
        else if (ret == -1)
        {
            free(trimmed);
            return -1; // error real
        }
        *map_line = trimmed;
        return 1;
    }
    return 0; // archivo terminó antes de mapa
}

void parse_file(t_config *config, int fd)
{
    char *map_line = NULL;
    int ret = parse_header(fd, config, &map_line);

    if (ret == -1)
        error_msg("Error\nFallo al parsear el header\n", config);
    if (!map_line)
        error_msg("Error\nMapa no encontrado\n", config);

    parse_map(fd, map_line, config);
}

