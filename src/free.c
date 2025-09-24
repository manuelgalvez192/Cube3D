/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaro-ro <mcaro-ro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 00:18:17 by mgalvez-          #+#    #+#             */
/*   Updated: 2025/09/24 16:07:44 by mcaro-ro         ###   ########.fr       */
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

static void	free_texture(mlx_texture_t **tex)
{
	if (tex && *tex)
	{
		mlx_delete_texture(*tex);
		*tex = NULL;
	}
}

void	free_mlx(t_config *config)
{
	if (!config)
		return ;
	free_texture(&config->texture_wall.nort);
	free_texture(&config->texture_wall.south);
	free_texture(&config->texture_wall.east);
	free_texture(&config->texture_wall.west);
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
