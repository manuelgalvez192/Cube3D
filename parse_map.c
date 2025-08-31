/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalvez- <mgalvez-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 03:20:43 by mgalvez-          #+#    #+#             */
/*   Updated: 2025/09/01 01:04:26 by mgalvez-         ###   ########.fr       */
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
        if (*line == '0' || *line == '1' || *line == 'N' || *line == 'S' || *line == 'E' || *line == 'W')
        {
            has_map_char = 1;
        }
        else if (*line != ' ' && *line != '\t' && *line != '\n')
        {
            printf("Caracter invalido en el mapa: '%c'\n", *line);
            return 0;
        }
        line++;
    }
    return has_map_char;
}

char **grow_map_array(char **old, int count, int new_cap)
{
    char **new;

    new = malloc(sizeof(char *) * new_cap);
    if (!new)
        return (NULL);
    for (int i = 0; i < count; ++i)
        new[i] = old[i];
    if (old)
        free(old);
    return (new);
}

void free_partial_map(char **map, int count)
{
    if (!map)
        return;
    for (int i = 0; i < count; ++i)
        free(map[i]);
    free(map);
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
