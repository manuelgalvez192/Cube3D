/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_chars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalvez- <mgalvez-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 17:38:04 by mgalvez-          #+#    #+#             */
/*   Updated: 2025/09/07 19:08:30 by mgalvez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	check_single_spawn(t_config *config)
{
	char	*row;
	int		spawn_count;
	int		i;
	int		j;

	spawn_count = 0;
	i = 0;
	while (i < config->map_rows)
	{
		row = config->map[i];
		j = 0;
		while (row[j])
		{
			if (row[j] == 'N' || row[j] == 'S'
				|| row[j] == 'E' || row[j] == 'W')
				spawn_count++;
			j++;
		}
		i++;
	}
	return (spawn_count == 1);
}

int	is_valid_neighbor(char c)
{
	return (c == '0' || c == '1' || c == 'N'
		|| c == 'S' || c == 'E' || c == 'W');
}

int	check_neighbors(t_config *config, int i, int j)
{
	char	c;
	int		rows;
	int		len_curr;

	rows = config->map_rows;
	c = config->map[i][j];
	if (c != '0' && c != 'N' && c != 'S' && c != 'E' && c != 'W')
		return (1);
	len_curr = ft_strlen(config->map[i]);
	if (j == 0 || !is_valid_neighbor(config->map[i][j - 1]))
		return (0);
	if (j + 1 >= len_curr || !is_valid_neighbor(config->map[i][j + 1]))
		return (0);
	if (i == 0 || j >= (int)ft_strlen(config->map[i - 1])
		|| !is_valid_neighbor(config->map[i - 1][j]))
		return (0);
	if (i + 1 >= rows || j >= (int)ft_strlen(config->map[i + 1])
		|| !is_valid_neighbor(config->map[i + 1][j]))
		return (0);
	return (1);
}

int	check_invalid_spaces(t_config *config)
{
	int		rows;
	int		i;
	int		j;

	rows = config->map_rows;
	i = 0;
	while (i < rows)
	{
		j = 0;
		while (config->map[i][j])
		{
			if (!check_neighbors(config, i, j))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}
