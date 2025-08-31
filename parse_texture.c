/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalvez- <mgalvez-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 00:52:58 by mgalvez-          #+#    #+#             */
/*   Updated: 2025/08/30 03:41:47 by mgalvez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int get_identifier(char *line)
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

int parse_texture_line(char *line, t_config *config)
{
    char *path;
    int id;

    id = get_identifier(line);
    if (id == 0)
    {
        if (line[0] == 'N' || line[0] == 'S' || line[0] == 'W' || line[0] == 'E')
            return (printf("Error\nIdentificador de textura inválido\n"), -1);
        return 0;
    }
    if (line[2] != ' ' && line[2] != '\t')
        return (printf("Error\nFormato inválido: espacio requerido después del identificador de textura\n"), -1);
    line += 2;
    while (*line == ' ' || *line == '\t')
        line++;
    if (*line == '\0')
        return (printf("Error\nFalta path en textura\n"), -1);
    path = ft_strdup(line);
    if (!path)
        return (printf("Error\nFallo al asignar memoria\n"), -1);
    if (id == 1)
        config->no_texture = path;
    else if (id == 2)
        config->so_texture = path;
    else if (id == 3)
        config->we_texture = path;
    else if (id == 4)
        config->ea_texture = path;
    return 1;
}

int parse_rgb(char *str, t_color *color)
{
	char	**components;

	components = ft_split(str, ',');
	if (!components || !components[0] || !components[1]
		|| !components[2] || components[3])
		return (free_split(components), printf("Error\nRGB invalido\n"), -1);
	color->r = ft_atoi(components[0]);
	color->g = ft_atoi(components[1]);
	color->b = ft_atoi(components[2]);
	free_split(components);
	if (color->r < 0 || color->r > 255 || color->g < 0 || color->g > 255
		|| color->b < 0 || color->b > 255)
		return (printf("Error\nValor RGB fuera de rango\n"), -1);
	return (0);
}

int parse_color_line(char *line, t_config *config)
{
    if (line[0] == 'F')
    {
        if (line[1] != ' ' && line[1] != '\t')
            return (printf("Error\nFormato inválido: espacio requerido después de F\n"), -1);
        line++;
        while (*line == ' ' || *line == '\t')
            line++;
        if (parse_rgb(line, &config->floor) == -1)
            return -1;
        return 1;
    }
    if (line[0] == 'C')
    {
        if (line[1] != ' ' && line[1] != '\t')
            return (printf("Error\nFormato inválido: espacio requerido después de C\n"), -1);
        line++;
        while (*line == ' ' || *line == '\t')
            line++;
        if (parse_rgb(line, &config->ceiling) == -1)
            return -1;
        return 1;
    }
    return 0;
}

