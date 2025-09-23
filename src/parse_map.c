/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaro-ro <mcaro-ro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 03:20:43 by mgalvez-          #+#    #+#             */
/*   Updated: 2025/09/23 18:31:23 by mcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "strings.h"

bool	is_valid_map_line(char *line)
{
	bool	has_map_char;
	char	*p;

	has_map_char = false;
	if (!line)
	{
		error_msg(MSG_ERR_INVALID_LINE);
		return (false);
	}
	p = line;
	while (*p && *p != '\n')
	{
		if (*p == '0' || *p == '1' || *p == 'N'
			|| *p == 'S' || *p == 'E' || *p == 'W')
			has_map_char = true;
		else if (*p != ' ' && *p != '\t')
			return (false);
		p++;
	}
	return (has_map_char);
}

int	count_remaining_map_lines(int fd)
{
	char	*line;
	int		count;

	count = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (!is_valid_map_line(line))
		{
			free(line);
			drain_gnl(fd);
			return (-1);
		}
		count++;
		free(line);
		line = get_next_line(fd);
	}
	return (count);
}

int	populate_map_from_fd(int fd, int rows, char *first_line,
	t_config *config)
{
	char	*line;
	int		idx;

	idx = 0;
	line = get_next_line(fd);
	while (line && idx < rows)
	{
		if (!is_valid_map_line(line))
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		if (idx == 0)
		{
			config->map[idx++] = first_line;
			free(line);
		}
		else
			config->map[idx++] = line;
		line = get_next_line(fd);
	}
	if (idx != rows)
		return (error_msg(MSG_ERR_ROW_COUNT_DONT_MATCH));
	return (EXIT_SUCCESS);
}

int	fill_map_from_file(const char *path, int rows, char *first_line,
	t_config *config)
{
	int		fd;
	bool	result;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (error_msg(MSG_ERR_OPENING_FILE));
	config->map = malloc(sizeof(char *) * (rows + 1));
	if (!config->map)
	{
		close(fd);
		return (error_msg(MSG_ERR_MALLOC_MAP));
	}
	result = populate_map_from_fd(fd, rows, first_line, config);
	config->map[rows] = NULL;
	config->map_rows = rows;
	close(fd);
	if (!check_single_spawn(config) || !check_invalid_spaces(config))
		return (error_msg(MSG_ERR_INVALID_MAP));
	return (result);
}

void	compute_map_dims(t_config *config)
{
	int		i;
	size_t	len;
	int		max_w;

	max_w = 0;
	i = 0;
	while (i < config->map_rows)
	{
		len = ft_strlen(config->map[i]) - 1;
		if ((int)len > max_w)
			max_w = (int)len;
		i++;
	}
	if (max_w < 1)
		config->map_width = 1;
	else
		config->map_width = max_w;
}
