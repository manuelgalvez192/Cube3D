/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalvez- <mgalvez-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 22:20:32 by mgalvez-          #+#    #+#             */
/*   Updated: 2025/08/30 03:24:15 by mgalvez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

# include "./libft/libft.h"
# include "./MLX42/include/MLX42/MLX42.h"
# include <stdbool.h>

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_config
{
	char	*no_texture;
	char	*so_texture;
	char	*we_texture;
	char	*ea_texture;
	t_color	floor;
	t_color	ceiling;
	char	**map;
	int		map_width;
	int		map_height;
	int		player_x;
	int		player_y;
	char	player_dir;
}	t_config;

/* --- MAIN --- */
bool	check_extension(const char *file_name, const char *extension);

/* --- PARSER --- */
int		parse_header(int fd, t_config *config, char **map_line);
void	parse_file(t_config *config, int fd);

/* --- PARSE TEXTURE --- */
int		get_identifier(char *line);
int		parse_texture_line(char *line, t_config *config);
int		parse_rgb(char *str, t_color *color);
int		parse_color_line(char *line, t_config *config);

/* --- PARSE MAP --- */
void	parse_map(int fd, char *first_line, t_config *config);

/* --- FREE --- */
void	free_split(char **split);
void	error_msg(char *msg, t_config *config);
void	free_config(t_config **config);

#endif
