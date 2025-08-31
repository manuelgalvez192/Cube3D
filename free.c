/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalvez- <mgalvez-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 00:18:17 by mgalvez-          #+#    #+#             */
/*   Updated: 2025/09/01 01:26:38 by mgalvez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void free_partial_map(char **map, int count)
{
    if (!map)
        return;
    for (int i = 0; i < count; ++i)
        free(map[i]);
    free(map);
}

void free_split(char **split)
{
	int i;

	if (!split)
		return;
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
	perror(msg);
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
