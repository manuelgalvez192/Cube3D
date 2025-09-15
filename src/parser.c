/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalvez- <mgalvez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 00:05:59 by mgalvez-          #+#    #+#             */
/*   Updated: 2025/09/15 18:03:39 by mgalvez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "strings.h"

int	validate_textures(t_config *config)
{
	if (!config->no_texture || !config->so_texture || !config->we_texture
		|| !config->ea_texture)
	{
		printf("Error\nMissing texture path(s)\n");
		free_config(&config);
		return (-1);
	}
	return (0);
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
	if (!is_valid_map_line(line, config))
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
		remaining_count = count_remaining_map_lines(fd, config);
		if (remaining_count == -1)
			return (-1);
		return (1 + remaining_count);
	}
	return (0);
}

void	parse_file(t_config *config, int fd)
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
		error_msg(MSG_ERR_PARSE_HEADER_OR_MAP, config);
		return ;
	}
	if (rows == 0 || !first_line)
	{
		if (first_line)
			free(first_line);
		error_msg(MSG_ERR_MAP_NOT_FOUND, config);
		return ;
	}
	if (validate_textures(config) == -1)
	{
		if (first_line)
			free(first_line);
		return ;
	}
	if (!fill_map_from_file(config->file_path, rows, first_line, config))
		return ;
	if (!check_single_spawn(config))
		error_msg(MSG_ERR_MAP_NOT_STARTING_POINT, config);
	config->map[(int)config->player_y][(int)config->player_x] = '0';
}
