/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalvez- <mgalvez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 03:20:43 by mgalvez-          #+#    #+#             */
/*   Updated: 2025/09/01 18:07:44 by mgalvez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int is_valid_map_line(char *line)
{
    int has_map_char;
    int in_map;
    int saw_space_after_map;
    char c;

    has_map_char = 0;
    in_map = 0;
    saw_space_after_map = 0;
    if (!line)
        return (0);
    while (*line && *line != '\n')
    {
        c = *line;
        if (!process_map_char(c, &in_map, &saw_space_after_map, &has_map_char))
            return (0);
        line++;
    }
    return (has_map_char);
}

void parse_map(int fd, char *first_line, t_config *config)
{
    char **tmp;
    char *line;
    int capacity;
    int i;

    capacity = 8;
    config->map_rows = 0;
    tmp = malloc(sizeof(char *) * capacity);
    if (!tmp)
    {
        free(first_line);
        return (error_msg("Error\nFallo al asignar memoria para el mapa\n", config), (void)0);
    }
    if (!is_valid_map_line(first_line))
    {
        free(first_line);
        free(tmp);
        return (error_msg("Error\nMapa contiene línea inválida\n", config), (void)0);
    }
    tmp[config->map_rows++] = first_line;
    while ((line = get_next_line(fd)))
    {
        if (!is_valid_map_line(line))
        {
            free(line);
            free_partial_map(tmp, config->map_rows);
            return (error_msg("Error\nMapa contiene línea inválida\n", config), (void)0);
        }
        if (config->map_rows == capacity)
        {
            int new_cap = capacity * 2;
            char **grown = grow_map_array(tmp, config->map_rows, new_cap);
            if (!grown)
            {
                free(line);
                free_partial_map(tmp, config->map_rows);
                return (error_msg("Error\nFallo al asignar memoria para el mapa\n", config), (void)0);
            }
            tmp = grown;
            capacity = new_cap;
        }
        tmp[config->map_rows++] = line;
    }
    config->map = malloc(sizeof(char *) * (config->map_rows + 1));
    if (!config->map)
    {
        free_partial_map(tmp, config->map_rows);
        return (error_msg("Error\nFallo al asignar memoria para el mapa\n", config), (void)0);
    }
    i = 0;
    while (i < config->map_rows)
    {
        config->map[i] = tmp[i];
        i++;
    }
    config->map[config->map_rows] = NULL;
    free(tmp);
    config->map_rows = config->map_rows;
}
