/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalvez- <mgalvez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 18:06:33 by mgalvez-          #+#    #+#             */
/*   Updated: 2025/09/01 18:07:52 by mgalvez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

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
        {
            printf("Caracter invalido: espacio en mitad de línea\n");
            return (0);
        }
        *has_map_char = 1;
        *in_map = 1;
    }
    else
    {
        printf("Caracter invalido en el mapa: '%c'\n", c);
        return (0);
    }
    return (1);
}
