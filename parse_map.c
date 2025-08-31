/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalvez- <mgalvez-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 03:20:43 by mgalvez-          #+#    #+#             */
/*   Updated: 2025/09/01 01:35:35 by mgalvez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int is_valid_map_line(char *line)
{
    int has_map_char = 0;
    int in_map = 0;              /* ya hemos empezado a ver chars de mapa */
    int saw_space_after_map = 0; /* vimos un espacio/tabs después de haber empezado el mapa */

    if (!line)
        return 0;

    while (*line && *line != '\n')
    {
        char c = *line;

        if (c == ' ' || c == '\t')
        {
            if (in_map)
                saw_space_after_map = 1; /* podría ser trailing; si luego aparece otro mapa -> error */
            /* si no estamos in_map, son espacios iniciales y se ignoran */
        }
        else if (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
        {
            if (saw_space_after_map)
            {
                /* Encontramos un mapa después de un espacio: espacio en mitad -> inválido */
                printf("Caracter invalido en el mapa: espacio en mitad de línea\n");
                return 0;
            }
            has_map_char = 1;
            in_map = 1;
        }
        else
        {
            printf("Caracter invalido en el mapa: '%c'\n", c);
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
