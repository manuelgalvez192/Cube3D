/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaro-ro <mcaro-ro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 00:18:17 by mgalvez-          #+#    #+#             */
/*   Updated: 2025/09/23 17:37:33 by mcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	free_partial_map(char **map, int count)
{
	int	i;

	i = 0;
	if (!map)
		return ;
	while (i < count)
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

int	error_msg(char *msg)
{
	printf("%s%s%s", COLOR_MSG_RED, msg, COLOR_MSG_RESET);
	return (EXIT_FAILURE);
}

void	free_mlx(t_config *config)
{
	if (config->texture_wall.east)
	{
		mlx_delete_texture(config->texture_wall.east);
		config->texture_wall.east = NULL;
	}
	if (config->texture_wall.nort)
	{
		mlx_delete_texture(config->texture_wall.nort);
		config->texture_wall.nort = NULL;
	}
	if (config->texture_wall.west)
	{
		mlx_delete_texture(config->texture_wall.west);
		config->texture_wall.west = NULL;
	}
	if (config->texture_wall.south)
	{
		mlx_delete_texture(config->texture_wall.south);
		config->texture_wall.south = NULL;
	}
	if (config->minimap.img)
	{
		mlx_delete_image(config->mlx, config->minimap.img);
		config->minimap.img = NULL;
	}
	if (config->img)
	{
		mlx_delete_image(config->mlx, config->img);
		config->img = NULL;
	}
	if (config->mlx)
	{
		mlx_close_window(config->mlx);
		mlx_terminate(config->mlx);
		config->mlx = NULL;
	}
	free_config(&config);
}

void	free_config(t_config **config)
{
	if (config && *config)
	{
		if ((*config)->no_texture)
			free((*config)->no_texture);
		if ((*config)->so_texture)
			free((*config)->so_texture);
		if ((*config)->we_texture)
			free((*config)->we_texture);
		if ((*config)->ea_texture)
			free((*config)->ea_texture);
		free_split((*config)->map);
		free((*config)->file_path);
		free(*config);
		*config = NULL;
	}
}
