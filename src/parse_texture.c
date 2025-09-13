/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaro-ro <mcaro-ro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 00:52:58 by mgalvez-          #+#    #+#             */
/*   Updated: 2025/09/13 23:05:44 by mcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "strings.h"

int	get_identifier(char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		return (1);
	if (ft_strncmp(line, "SO ", 3) == 0)
		return (2);
	if (ft_strncmp(line, "WE ", 3) == 0)
		return (3);
	if (ft_strncmp(line, "EA ", 3) == 0)
		return (4);
	return (0);
}

void	path_maker(t_config *config, char *line, int id)
{
	char	*path;

	path = ft_strdup(line);
	if (!path)
	{
		printf(MSG_ERR_MEMORY_ALOCATION);
		return ;
	}
	if (id == 1)
		config->no_texture = path;
	else if (id == 2)
		config->so_texture = path;
	else if (id == 3)
		config->we_texture = path;
	else if (id == 4)
		config->ea_texture = path;
	// free(path);
}

int	parse_texture_line(char *line, t_config *config)
{
	int	id;

	id = get_identifier(line);
	if (id == 0)
	{
		if (line[0] == 'N' || line[0] == 'S'
			|| line[0] == 'W' || line[0] == 'E')
			return (printf(MSG_ERR_TEXTURE_IDENTIFIER), -1);
		return (0);
	}
	if (line[2] != ' ' && line[2] != '\t')
		return (printf(MSG_ERR_TEXTURE_FORMAT), -1);
	line += 2;
	while (*line == ' ' || *line == '\t')
		line++;
	if (*line == '\0')
		return (printf(MSG_ERR_TEXTURE_PATH), -1);
	path_maker(config, line, id);
	return (1);
}

int	parse_rgb(char *str, t_color *color)
{
	char	**components;

	components = ft_split(str, ',');
	if (!components || !components[0] || !components[1]
		|| !components[2] || components[3])
		return (free_split(components), printf(MSG_ERR_RGB), -1);
	color->r = ft_atoi(components[0]);
	color->g = ft_atoi(components[1]);
	color->b = ft_atoi(components[2]);
	free_split(components);
	if (color->r < 0 || color->r > 255 || color->g < 0 || color->g > 255
		|| color->b < 0 || color->b > 255)
		return (printf(MSG_ERR_RGB_OUT_OF_RANGE), -1);
	return (0);
}

int	parse_color_line(char *line, t_config *config)
{
	if (line[0] == 'F')
	{
		if (line[1] != ' ' && line[1] != '\t')
			return (printf(MSG_ERR_FORMAT_SPACE_BEFORE "F\n"), -1);
		line++;
		while (*line == ' ' || *line == '\t')
			line++;
		if (parse_rgb(line, &config->floor) == -1)
			return (-1);
		return (1);
	}
	if (line[0] == 'C')
	{
		if (line[1] != ' ' && line[1] != '\t')
			return (printf(MSG_ERR_FORMAT_SPACE_BEFORE "C\n"), -1);
		line++;
		while (*line == ' ' || *line == '\t')
			line++;
		if (parse_rgb(line, &config->ceiling) == -1)
			return (-1);
		return (1);
	}
	return (0);
}
