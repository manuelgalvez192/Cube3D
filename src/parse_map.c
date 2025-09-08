/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaro-ro <mcaro-ro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 03:20:43 by mgalvez-          #+#    #+#             */
/*   Updated: 2025/09/08 06:48:00 by mcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

int is_valid_map_line(char *line, t_config *config)
{
	int		has_map_char;
	char 	*p;

	has_map_char = 0;
	p = line;
	if (!line)
		return (error_msg("Error\nMapa contiene línea inválida\n", config), 0);
	while (*p && *p != '\n')
	{
		if (*p == '0' || *p == '1' || *p == 'N' || *p == 'S' || *p == 'E' || *p == 'W')
			has_map_char = 1;
		else if (*p != ' ' && *p != '\t')
		{
			if (config->map_rows > 0)
				return (error_msg("Error\nMapa contiene carácter inválido\n", config), 0);
			return (0);
		}
		p++;
	}
	return (has_map_char);
}

bool	populate_map_from_fd(int fd, int rows, char *first_line, t_config *config)
{
	char	*line;
	int		idx;

	idx = 0;
	while ((line = get_next_line(fd)) && idx < rows)
	{
		if (!is_valid_map_line(line, config))
		{
			free(line);
			continue ;
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
	return (true);
}

bool	fill_map_from_file(const char *path, int rows, char *first_line, t_config *config)
{
	int		fd;
	bool	ok;

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
	if (!check_single_spawn(config) || !check_invalid_spaces(config))
		error_msg("Error\nMapa inválido\n", config);
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
