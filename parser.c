/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalvez- <mgalvez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 00:05:59 by mgalvez-          #+#    #+#             */
/*   Updated: 2025/09/02 20:15:48 by mgalvez-         ###   ########.fr       */
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

int process_header_line(char *line, t_config *config, char **map_line)
{
    char *trimmed;
    int   ret;

    trimmed = ft_strtrim(line, " \t\n");
    if (!trimmed || *trimmed == '\0')
    {
        free(line);
        free(trimmed);
        return (0);
    }
    ret = handle_texture_and_color(trimmed, config);
    if (ret == -1)
        return (free(trimmed), free(line), -1);
    if (ret == 1)
        return (free(trimmed), free(line), 0);
    *map_line = ft_strdup(line);
    if (!*map_line)
        return (free(trimmed), free(line), -1);
    free(trimmed);
    free(line);
    config->map_rows += 1;
    return (1);
}

int parse_header(int fd, t_config *config, char **map_line)
{
    char *line;
    int   ret;

    while ((line = get_next_line(fd)))
    {
        ret = process_header_line(line, config, map_line);
        if (ret != 0)
            return (ret);
    }
    return (0);
}

void parse_file(t_config *config, int fd)
{
    char *first_line;
    int   rows;

    first_line = NULL;
    rows = count_map_rows_and_capture_first(fd, config, &first_line);
    close(fd);
    if (rows == -1)
    {
        if (first_line)
            free(first_line);
        error_msg("Error\nFallo al parsear el header o mapa (primera pasada)\n", config);
        return;
    }
    if (rows == 0 || !first_line)
    {
        if (first_line) free(first_line);
        error_msg("Error\nMapa no encontrado\n", config);
        return;
    }
    if (!fill_map_from_file(config->file_path, rows, first_line, config))
        return;
}
