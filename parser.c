/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalvez- <mgalvez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 00:05:59 by mgalvez-          #+#    #+#             */
/*   Updated: 2025/09/01 18:10:42 by mgalvez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int handle_texture_and_color(char *trimmed, t_config *config)
{
    int ret;

    ret = parse_texture_line(trimmed, config);
    if (ret == 1 || ret == -1)
        return (ret);
    ret = parse_color_line(trimmed, config);
    if (ret == 1 || ret == -1)
        return (ret);
    return 0;
}

int parse_header(int fd, t_config *config, char **map_line)
{
    char    *line;
    char    *trimmed;
    int     ret;

    while ((line = get_next_line(fd)))
    {
        trimmed = ft_strtrim(line, " \t\n");
        if (!trimmed || *trimmed == '\0')
        {
            free(line);
            free(trimmed);
            continue;
        }
        ret = handle_texture_and_color(trimmed, config);
        if (ret == -1)
            return (free(trimmed), free(line), -1);
        if (ret == 1)
        {
            free(trimmed);
            free(line);
            continue;
        }
        *map_line = ft_strdup(line);
        if (!*map_line)
            return (free(trimmed), free(line), -1);
        free(trimmed);
        free(line);
        config->map_rows += 1;
        return (1);
    }
    return (0);
}

void parse_file(t_config *config, int fd)
{
    char *map_line;
    int ret;

    map_line = NULL;
    config->map_rows = 0;
    ret = parse_header(fd, config, &map_line);
    if (ret == -1)
        error_msg("Error\nFallo al parsear el header\n", config);
    if (!map_line)
        error_msg("Error\nMapa no encontrado\n", config);
    parse_map(fd, map_line, config);
}
