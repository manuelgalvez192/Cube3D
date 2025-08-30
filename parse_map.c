/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalvez- <mgalvez-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 03:20:43 by mgalvez-          #+#    #+#             */
/*   Updated: 2025/08/30 03:30:23 by mgalvez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int is_valid_map_line(char *line)
{
    int has_map_char = 0;

    if (!line)
        return 0;

    while (*line)
    {
        if (*line == '0' || *line == '1' || *line == 'N' || *line == 'S' 
            || *line == 'E' || *line == 'W')
        {
            has_map_char = 1; // línea tiene al menos un carácter válido
        }
        else if (*line != ' ' && *line != '\t' && *line != '\n')
        {
            // cualquier otro carácter no permitido → inválido
            return 0;
        }
        line++;
    }

    // si no hay caracteres de mapa → inválido
    return has_map_char;
}

void parse_map(int fd, char *first_line, t_config *config)
{
    char **map = NULL;
    char *line;
    int rows = 0;

    map = malloc(sizeof(char *) * 1024);
    if (!map)
        error_msg("Error\nFallo al asignar memoria para el mapa\n", config);

    if (!is_valid_map_line(first_line))
        error_msg("Error\nMapa contiene línea inválida\n", config);
    map[rows++] = first_line;

    while ((line = get_next_line(fd)))
    {
        if (!is_valid_map_line(line))
        {
            free(line);
            error_msg("Error\nMapa contiene línea inválida\n", config);
        }
        map[rows++] = line;
    }

    map[rows] = NULL;
    config->map = map;
}

