/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalvez- <mgalvez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 00:18:17 by mgalvez-          #+#    #+#             */
/*   Updated: 2025/09/02 20:30:05 by mgalvez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void drain_gnl(int fd)
{
    char *tmp;
    while ((tmp = get_next_line(fd)))
        free(tmp);
}

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
