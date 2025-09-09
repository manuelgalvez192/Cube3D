/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaro-ro <mcaro-ro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 05:50:43 by mcaro-ro          #+#    #+#             */
/*   Updated: 2025/09/09 07:18:12 by mcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cube.h"
#include <math.h>

static void	move_forward(t_config *config)
{
	int	double_x;
	int	double_y;
	int	new_x;
	int	new_y;	

	get_direction_x(config->player_angle, &double_x);
	get_direction_y(config->player_angle, &double_y);
	new_x = config->player_x + double_x;
	new_y = config->player_y + double_y;
	if (is_walkable(config, new_x, new_y))
	{
		config->player_x = new_x;
		config->player_y = new_y;
	}
}

static void	move_backward(t_config *config)
{
	int	double_x;
	int	double_y;
	int	new_x;
	int	new_y;	

	get_direction_x(config->player_angle, &double_x);
	get_direction_y(config->player_angle, &double_y);
	new_x = config->player_x - double_x;
	new_y = config->player_y - double_y;
	if (is_walkable(config, new_x, new_y))
	{
		config->player_x = new_x;
		config->player_y = new_y;
	}
}

static void	strafe_left(t_config *config)
{
	int	double_x;
	int	double_y;
	int	new_x;
	int	new_y;	

	get_direction_x(config->player_angle - M_PI / 2, &double_x);
	get_direction_y(config->player_angle - M_PI / 2, &double_y);
	new_x = config->player_x + double_x;
	new_y = config->player_y + double_y;
	if (is_walkable(config, new_x, new_y))
	{
		config->player_x = new_x;
		config->player_y = new_y;
	}
}

static void	strafe_right(t_config *config)
{
	int	double_x;
	int	double_y;
	int	new_x;
	int	new_y;	

	get_direction_x(config->player_angle + M_PI / 2, &double_x);
	get_direction_y(config->player_angle + M_PI / 2, &double_y);
	new_x = config->player_x + double_x;
	new_y = config->player_y + double_y;
	if (is_walkable(config, new_x, new_y))
	{
		config->player_x = new_x;
		config->player_y = new_y;
	}
}

void	update_player_movement(t_config *config)
{
	static double	last_move = 0;

	if (!can_move(&last_move, 60))
		return ;
	if (config->player_move.up)
		move_forward(config);
	if (config->player_move.down)
		move_backward(config);
	if (config->player_move.left)
		strafe_left(config);
	if (config->player_move.right)
		strafe_right(config);
}
