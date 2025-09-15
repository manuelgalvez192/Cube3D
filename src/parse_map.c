/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalvez- <mgalvez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 03:20:43 by mgalvez-          #+#    #+#             */
/*   Updated: 2025/09/15 17:33:37 by mgalvez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "strings.h"

int	is_valid_map_line(char *line, t_config *config)
{
	int		has_map_char;
	char	*p;

	has_map_char = 0;
	p = line;
	if (!line)
		return (error_msg(MSG_ERR_INVALID_LINE, config), 0);
	while (*p && *p != '\n')
	{
		if (*p == '0' || *p == '1' || *p == 'N'
			|| *p == 'S' || *p == 'E' || *p == 'W')
			has_map_char = 1;
		else if (*p != ' ' && *p != '\t')
		{
			if (config->map_rows > 0)
				return (error_msg(MSG_ERR_INVALID_CHAR, config), 0);
			return (0);
		}
		p++;
	}
	return (has_map_char);
}

bool	populate_map_from_fd(int fd, int rows, char *first_line,
	t_config *config)
{
	char	*line;
	int		idx;

	idx = 0;
	line = get_next_line(fd);
	while (line && idx < rows)
	{
		if (!is_valid_map_line(line, config))
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
		return (error_msg(MSG_ERR_ROW_COUNT_DONT_MATCH, config), false);
	return (true);
}

bool	fill_map_from_file(const char *path, int rows, char *first_line,
	t_config *config)
{
	int		fd;
	bool	ok;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (error_msg(MSG_ERR_OPENING_FILE, config), false);
	config->map = malloc(sizeof(char *) * (rows + 1));
	if (!config->map)
	{
		close(fd);
		return (error_msg(MSG_ERR_MALLOC_MAP, config), false);
	}
	ok = populate_map_from_fd(fd, rows, first_line, config);
	config->map[rows] = NULL;
	config->map_rows = rows;
	close(fd);
	if (!check_single_spawn(config) || !check_invalid_spaces(config))
		error_msg(MSG_ERR_INVALID_MAP, config);
	return (ok);
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
