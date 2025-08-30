/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalvez- <mgalvez-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 00:18:17 by mgalvez-          #+#    #+#             */
/*   Updated: 2025/08/30 02:40:22 by mgalvez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void free_raw_map(char **raw_map, int count)
{
    int i = 0;
    if (!raw_map)
        return;
    while (i < count)
    {
        free(raw_map[i]);
        i++;
    }
    free(raw_map);
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
		free((*config)->map);
		free(*config);
		*config = NULL;
	}
	exit(0);
}
