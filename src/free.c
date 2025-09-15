/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalvez- <mgalvez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 00:18:17 by mgalvez-          #+#    #+#             */
/*   Updated: 2025/09/15 18:21:28 by mgalvez-         ###   ########.fr       */
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

void	error_msg(char *msg, t_config *config)
{
	printf("%s", msg);
	free_config(&config);
	exit(1);
}

void	free_mlx(t_config *config)
{
	if (config->texture_wall.east)
		mlx_delete_texture(config->texture_wall.east);
	if (config->texture_wall.nort)
		mlx_delete_texture(config->texture_wall.nort);
	if (config->texture_wall.west)
		mlx_delete_texture(config->texture_wall.west);
	if (config->texture_wall.south)
		mlx_delete_texture(config->texture_wall.south);
	if (config->minimap.img)
		mlx_delete_image(config->mlx, config->minimap.img);
	if (config->img)
		mlx_delete_image(config->mlx, config->img);
	free_config(&config);
	mlx_terminate(config->mlx);
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
	exit(0);
}
