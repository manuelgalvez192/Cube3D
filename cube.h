/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalvez- <mgalvez-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 22:20:32 by mgalvez-          #+#    #+#             */
/*   Updated: 2025/09/07 19:09:32 by mgalvez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

# include "./libft/libft.h"
# include "./MLX42/include/MLX42/MLX42.h"
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>

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
	int		map_rows;
	int		map_width;
	int		map_height;
	int		player_x;
	int		player_y;
	char	player_dir;
	char	*file_path;
}	t_config;

/* --- MAIN --- */
bool	check_extension(const char *file_name, const char *extension);

/* --- PARSER --- */
int		handle_texture_and_color(char *trimmed, t_config *config);
int		process_config_line(char *line, t_config *config, char **first_line_out);
int		count_remaining_map_lines(int fd, t_config *config);
int		count_map_rows_and_capture_first(int fd, t_config *config, char **first_line_out);
void	parse_file(t_config *config, int fd);

/* --- PARSE TEXTURE --- */
int		get_identifier(char *line);
void	path_maker(t_config *config, char *line, int id);
int		parse_texture_line(char *line, t_config *config);
int		parse_rgb(char *str, t_color *color);
int		parse_color_line(char *line, t_config *config);

/* --- PARSE MAP --- */
int		is_valid_map_line(char *line, t_config *config);
bool	populate_map_from_fd(int fd, int rows, char *first_line, t_config *config);
bool	fill_map_from_file(const char *path, int rows, char *first_line, t_config *config);

/* --- CHECK CHARS --- */
int		check_single_spawn(t_config *config);
int		is_valid_neighbor(char c);
int		check_neighbors(t_config *config, int i, int j);
int		check_invalid_spaces(t_config *config);

/* --- FREE --- */
void	drain_gnl(int fd);
void	free_partial_map(char **map, int count);
void	free_split(char **split);
void	error_msg(char *msg, t_config *config);
void	free_config(t_config **config);

#endif
