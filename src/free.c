/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaro-ro <mcaro-ro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 00:18:17 by mgalvez-          #+#    #+#             */
/*   Updated: 2025/09/10 20:18:21 by mcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	drain_gnl(int fd)
{
	char	*tmp;

	while ((tmp = get_next_line(fd)))
		free(tmp);
}

void	free_partial_map(char **map, int count)
{
	int	i;

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

void	free_config(t_config **config)
{
	if (config && *config)
	{
		free_split((*config)->map);
		free((*config)->file_path);
		free(*config);
		*config = NULL;
	}
	exit(0);
}
