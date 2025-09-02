/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalvez- <mgalvez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 18:06:33 by mgalvez-          #+#    #+#             */
/*   Updated: 2025/09/02 20:06:15 by mgalvez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

char **grow_map_array(char **old, int count, int new_cap)
{
    char **new;

    new = malloc(sizeof(char *) * new_cap);
    if (!new)
        return (printf("Error\nFallo al asignar memoria para el mapa\n"), NULL);
    for (int i = 0; i < count; ++i)
        new[i] = old[i];
    if (old)
        free(old);
    return (new);
}

int is_map_char(char c)
{
    return (c == '0' || c == '1' || c == 'N'
        || c == 'S' || c == 'E' || c == 'W');
}

int process_map_char(char c, int *in_map, int *saw_space, int *has_map_char)
{
    if (c == ' ' || c == '\t')
    {
        if (*in_map)
            *saw_space = 1;
    }
    else if (is_map_char(c))
    {
        if (*saw_space)
            return 0;
        *has_map_char = 1;
        *in_map = 1;
    }
    else
        return 0;
    return 1;
}

int is_valid_map_line(char *line, t_config *config)
{
    int has_map_char;
    int in_map;
    int saw_space_after_map;
    char c;
    char *p;

    if (!line)
        return (error_msg("Error\nMapa contiene línea inválida\n", config), 0);
    has_map_char = 0;
    in_map = 0;
    saw_space_after_map = 0;
    p = line;
    while (*p && *p != '\n')
    {
        c = *p;
        if (!process_map_char(c, &in_map, &saw_space_after_map, &has_map_char))
        {
            if (config->map_rows > 0)
                return (error_msg("Error\nMapa contiene línea inválida\n", config), 0);
            return 0;
        }
        p++;
    }
    return (has_map_char);
}

