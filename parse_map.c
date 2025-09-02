/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalvez- <mgalvez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 03:20:43 by mgalvez-          #+#    #+#             */
/*   Updated: 2025/09/02 21:04:16 by mgalvez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

bool reading_map(int *capacity, int fd, char ***tmp_ptr, t_config *config)
{
    char *line;
    char **grown;
    char **tmp;
    int new_cap;

    tmp = *tmp_ptr;
    while ((line = get_next_line(fd)))
    {
        if (!is_valid_map_line(line, config))
            return (free(line), false);

        if (config->map_rows == *capacity)
        {
            new_cap = (*capacity) * 2;
            grown = grow_map_array(tmp, config->map_rows, new_cap);
            if (!grown)
                return (free(line), false);
            tmp = grown;
            *capacity = new_cap;
            *tmp_ptr = tmp;
        }
        tmp[config->map_rows++] = line;
    }
    return true;
}

void parse_map(int fd, char *first_line, t_config *config)
{
    char **tmp;
    int capacity;
    int i;

    capacity = 0;
    config->map_rows = 0;
    tmp = malloc(sizeof(char *) * capacity);
    if (!tmp)
    {
        free(first_line);
        error_msg("Error\nFallo al asignar memoria para el mapa\n", config);
    }
    if (!is_valid_map_line(first_line, config))
    {
        free(first_line);
        free(tmp);
        error_msg("Error\nFallo al asignar memoria para el mapa\n", config);
    }
    tmp[config->map_rows++] = first_line;
    if (!reading_map(&capacity, fd, &tmp, config))
        return;
    config->map = malloc(sizeof(char *) * (config->map_rows + 1));
    if (!config->map)
        error_msg("Error\nFallo al asignar memoria para el mapa\n", config);
    i = -1;
    while (++i < config->map_rows)
        config->map[i] = tmp[i];
    config->map[config->map_rows] = NULL;
    free(tmp);
    config->map_rows = config->map_rows;
}

int count_map_rows_and_capture_first(int fd, t_config *config, char **first_line_out)
{
    char *line = NULL;
    char *trim = NULL;
    int ret;
    int count = 0;

    *first_line_out = NULL;
    while ((line = get_next_line(fd)))
    {
        trim = ft_strtrim(line, " \t\n");
        if (!trim)
        {
            free(line);
            drain_gnl(fd);
            return -1;
        }
        if (*trim == '\0')
        {
            free(trim);
            free(line);
            continue;
        }
        ret = handle_texture_and_color(trim, config);
        free(trim);
        if (ret == -1)
        {
            free(line);
            drain_gnl(fd);
            return -1;
        }
        if (ret == 1)
        {
            free(line);
            continue;
        }
        if (!is_valid_map_line(line, config))
        {
            free(line);
            drain_gnl(fd);
            return -1;
        }
        *first_line_out = ft_strdup(line);
        if (!*first_line_out)
        {
            free(line);
            drain_gnl(fd);
            return -1;
        }
        free(line);
        count = 1;
        while ((line = get_next_line(fd)))
        {
            if (!is_valid_map_line(line, config))
            {
                free(line);
                drain_gnl(fd);
                return -1;
            }
            count++;
            free(line);
        }
        return count;
    }
    return 0;
}

bool populate_map_from_fd(int fd, int rows, char *first_line, t_config *config)
{
    char *line;
    int idx;

    idx = 0;
    while ((line = get_next_line(fd)) && idx < rows)
    {
        if (!is_valid_map_line(line, config))
        {
            free(line);
            continue;
        }
        if (idx == 0)
        {
            config->map[idx++] = first_line;
            free(line);
        }
        else
            config->map[idx++] = line;
    }
    if (idx != rows)
        return (error_msg("Error\nConteo de filas no coincide\n", config), false);
    return true;
}

bool fill_map_from_file(const char *path, int rows, char *first_line, t_config *config)
{
    int fd;
    bool ok;

    fd = open(path, O_RDONLY);
    if (fd < 0)
        return (error_msg("Error\nNo se pudo reabrir el archivo\n", config), false);
    config->map = malloc(sizeof(char *) * (rows + 1));
    if (!config->map)
    {
        close(fd);
        return (error_msg("Error\nFallo malloc mapa\n", config), false);
    }
    ok = populate_map_from_fd(fd, rows, first_line, config);
    config->map[rows] = NULL;
    config->map_rows = rows;
    close(fd);
    return ok;
}
