/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaro-ro <mcaro-ro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 00:05:59 by mgalvez-          #+#    #+#             */
/*   Updated: 2025/09/23 18:29:45 by mcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	validate_textures(t_config *config)
{
	if (!config->no_texture || !config->so_texture || !config->we_texture
		|| !config->ea_texture)
		return (error_msg("Error\tMissing texture path(s)\n"));
	return (EXIT_SUCCESS);
}

int	handle_texture_and_color(char *trimmed, t_config *config)
{
	int	ret;

	ret = parse_texture_line(trimmed, config);
	if (ret == 1 || ret == -1)
		return (ret);
	ret = parse_color_line(trimmed, config);
	if (ret == 1 || ret == -1)
		return (ret);
	return (0);
}

int	process_config_line(char *line, t_config *config, char **first_line_out)
{
	char	*trim;
	int		ret;

	trim = ft_strtrim(line, " \t\n");
	if (!trim)
		return (-1);
	if (*trim == '\0')
	{
		free(trim);
		return (0);
	}
	ret = handle_texture_and_color(trim, config);
	free(trim);
	if (ret == -1)
		return (-1);
	if (ret == 1)
		return (0);
	if (!is_valid_map_line(line))
		return (-1);
	*first_line_out = ft_strdup(line);
	if (!*first_line_out)
		return (-1);
	return (1);
}

int	count_map_rows_and_capture_first(int fd, t_config *config,
	char **first_line_out)
{
	char	*line;
	int		ret;
	int		remaining_count;

	*first_line_out = NULL;
	line = get_next_line(fd);
	while (line)
	{
		ret = process_config_line(line, config, first_line_out);
		if (ret == -1)
			return (free(line), drain_gnl(fd), -1);
		if (ret == 0)
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		free(line);
		remaining_count = count_remaining_map_lines(fd);
		if (remaining_count == -1)
			return (-1);
		return (1 + remaining_count);
	}
	return (0);
}

int	parse_file(t_config *config, int fd)
{
	char	*first_line;
	int		rows;

	first_line = NULL;
	rows = count_map_rows_and_capture_first(fd, config, &first_line);
	close(fd);
	if (rows == -1)
	{
		if (first_line)
			free(first_line);
		return (error_msg(MSG_ERR_PARSE_HEADER_OR_MAP));
	}
	if (rows == 0 || !first_line)
	{
		if (first_line)
			free(first_line);
		return (error_msg(MSG_ERR_MAP_NOT_FOUND));
	}
	if (validate_textures(config) == EXIT_FAILURE)
	{
		if (first_line)
			free(first_line);
		return (EXIT_FAILURE);
	}
	if (fill_map_from_file(config->file_path, rows, first_line, config) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (!check_single_spawn(config))
		return (error_msg(MSG_ERR_MAP_NOT_STARTING_POINT));
	config->map[(int)config->player_y][(int)config->player_x] = '0';
	return (EXIT_SUCCESS);
}
