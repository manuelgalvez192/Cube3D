/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaro-ro <mcaro-ro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 22:20:32 by mgalvez-          #+#    #+#             */
/*   Updated: 2025/09/08 04:47:52 by mcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

# include "./libft/libft.h"
# include "./MLX42/include/MLX42/MLX42.h"
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>

# define WIDTH			1280
# define HEIGHT			720
# define TILE_SIZE		10
# define MINIMAP_RATIO	0.35f
# define MINIMAP_MARGIN	10
# define BORDER_COLOR 0x000000FF

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct  s_minimap
{
	mlx_image_t	*img2d;
	int			tile;
	int			width;
	int			height;
	int			x_off;
	int			y_off;
}	t_minimap;

typedef struct s_config
{
	char		*no_texture;
	char		*so_texture;
	char		*we_texture;
	char		*ea_texture;
	t_color		floor;
	t_color		ceiling;
	char		**map;
	int			map_rows;
	int			map_width;
	int			map_height;
	int			player_x;
	int			player_y;
	char		player_dir;
	char		*file_path;
	mlx_t		*mlx;
	mlx_image_t	*img3d;
	t_minimap	minimap;
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

/* --- MLX --- */
void	put_pixel_safe(mlx_image_t *img, int x, int y, uint32_t color);
void	clear_image(mlx_image_t *img);
void	on_resize(int new_w, int new_h, void *param);
void	run_game(t_config *config);

/* --- RENDER --- */
void	render(void *param);

/* --- 3D --- */
void	render3d(t_config *config);

/* --- 2D --- */
void	draw_square(int x, int y, int size, uint32_t color, mlx_image_t *img);
void	draw_square_border(int x, int y, int size, uint32_t color, mlx_image_t *img);
void	draw_map_on_image(t_config *config);
void	compute_minimap(t_config *config);
void	compute_map_dims(t_config *config);
void	render2d(void *param);

/* --- FREE --- */
void	drain_gnl(int fd);
void	free_partial_map(char **map, int count);
void	free_split(char **split);
void	error_msg(char *msg, t_config *config);
void	free_config(t_config **config);

#endif
