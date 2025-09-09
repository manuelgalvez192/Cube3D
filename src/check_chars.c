/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_chars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaro-ro <mcaro-ro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 17:38:04 by mgalvez-          #+#    #+#             */
/*   Updated: 2025/09/09 04:47:54 by mcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

int	check_single_spawn(t_config *config)
{
	int		spawn_count;
	int		i;
	int		j;

	i = 0;
	spawn_count = 0;
	while (i < config->map_rows)
	{
		j = 0;
		while (config->map[i][j])
		{
			if (config->map[i][j] == 'N' || config->map[i][j] == 'S'
				|| config->map[i][j] == 'E' || config->map[i][j] == 'W')
			{
				config->player_x = j;
				config->player_y = i;
				config->player_dir = config->map[i][j];
				config->player_angle = get_initial_angle(config->player_dir);
				spawn_count++;
			}
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
