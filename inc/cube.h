/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaro-ro <mcaro-ro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 22:20:32 by mgalvez-          #+#    #+#             */
/*   Updated: 2025/09/23 18:05:12 by mcaro-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

# include "../libft/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"

# include "strings.h"
# include "colors.h"
# include "paths.h"

# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>

/* --- PLAYER --- */
# define PLAYER_ROT_SPEED	2.0f
# define PLAYER_RADIUS		0.2f
# define PLAYER_SPEED		2.0f
# define PLAYER_CENTER_OFF	0.5f

/* --- WINDOW --- */
# define WIDTH				1280
# define HEIGHT				720

/* -- MINIMAP --- */
# define TILE_SIZE			10
# define MINIMAP_RATIO		0.45f
# define MINIMAP_MARGIN		10

/* --- RAYCASTING --- */
# define FOV				1.0471975511965977461542144610932f
# define OFFSET_EPSILON		0.0001

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef enum e_wall_side
{
	NORTH,
	SOUTH,
	EAST,
	WEST
}	t_wall_side;

typedef struct s_col_data
{
	int				x;
	int				height;
	int				tex_x;
	mlx_texture_t	*tex;
}	t_col_data;

typedef struct s_texture
{
	mlx_texture_t	*nort;
	mlx_texture_t	*south;
	mlx_texture_t	*east;
	mlx_texture_t	*west;
}	t_texture;

typedef struct s_raydda
{
	double	pos_x;
	double	pos_y;
	int		map_x;
	int		map_y;
	double	dir_x;
	double	dir_y;
	double	delta_x;
	double	delta_y;
	double	side_x;
	double	side_y;
	int		step_x;
	int		step_y;
	int		side;
}	t_raydda;

typedef struct s_rayhit
{
	int		hit;
	int		side;
	int		map_x;
	int		map_y;
	float	perp_dist;
	float	wall_x;
	float	ray_x;
	float	ray_y;
}	t_rayhit;

typedef struct s_rect
{
	int	x;
	int	y;
	int	size;
	int	w;
	int	h;
}	t_rect;

typedef struct s_minimap
{
	mlx_image_t	*img;
	int			tile;
	int			width;
	int			height;
	int			x_off;
	int			y_off;
	bool		visibility;
}	t_minimap;

typedef struct s_player_move
{
	bool	up;
	bool	down;
	bool	left;
	bool	right;
	bool	rotate_left;
	bool	rotate_right;
}	t_player_move;

typedef struct s_config
{
	char			*no_texture;
	char			*so_texture;
	char			*we_texture;
	char			*ea_texture;
	t_color			floor;
	t_color			ceiling;
	char			**map;
	int				map_rows;
	int				map_width;
	int				map_height;
	float			player_x;
	float			player_y;
	char			player_dir;
	double			player_angle;
	t_player_move	player_move;
	char			*file_path;
	mlx_t			*mlx;
	mlx_image_t		*img;
	t_minimap		minimap;
	t_texture		texture_wall;
}	t_config;

/* --- MAIN --- */
void			drain_gnl(int fd);
bool			check_extension(const char *arg, const char *extension);

/* --- PARSER --- */
int				validate_textures(t_config *config);
int				handle_texture_and_color(char *trimmed, t_config *config);
int				process_config_line(char *line, t_config *config,
					char **first_line_out);
int				count_map_rows_and_capture_first(int fd, t_config *config,
					char **first_line_out);
int				parse_file(t_config *config, int fd);

/* --- PARSE TEXTURE --- */
int				get_identifier(char *line);
void			path_maker(t_config *config, char *line, int id);
int				parse_texture_line(char *line, t_config *config);
int				parse_rgb(char *str, t_color *color);
int				parse_color_line(char *line, t_config *config);

/* --- PARSE MAP --- */
int				is_valid_map_line(char *line, t_config *config);
int				count_remaining_map_lines(int fd, t_config *config);
int				populate_map_from_fd(int fd, int rows, char *first_line,
					t_config *config);
int				fill_map_from_file(const char *path, int rows, char *first_line,
					t_config *config);

/* --- CHECK CHARS --- */
int				check_single_spawn(t_config *config);
int				is_valid_neighbor(char c);
int				check_neighbors(t_config *config, int i, int j);
int				check_invalid_spaces(t_config *config);

/* --- MLX --- */
void			put_pixel_safe(mlx_image_t *img, int x, int y, uint32_t color);
void			clear_image(mlx_image_t *img);
void			on_resize(int new_w, int new_h, void *param);
void			on_key(mlx_key_data_t keydata, void *param);
int				run_game(t_config *config);

/* --- RENDER --- */
void			render(void *param);
int				is_wall_cell(t_config *config, int mx, int my);
void			hit_init(t_rayhit *hit, t_raydda dda);
void			dda_init_state(t_config *config, t_raydda *dda,
					double rx, double ry);
int				dda_step_cell(t_config *config, t_raydda *dda);
t_rayhit		dda_cast(t_config *config, double rx, double ry);

/* --- 3D --- */
void			render3d(t_config *config);
void			render_column(t_config *config, int x);
t_wall_side		side_from_hit(const t_rayhit *hit);
mlx_texture_t	*get_wall_texture(t_config *config, t_wall_side side);
int				tex_x_from_hit(const t_rayhit *hit, const mlx_texture_t *tex);
int				get_texture_pixel(mlx_texture_t *tex, int x, int y);

/* --- 2D --- */
void			draw_fill_sq(t_rect rect, uint32_t color, mlx_image_t *img);
void			draw_square(t_rect rect, uint32_t color, mlx_image_t *img);
void			draw_map_on_image(t_config *config);
void			draw_ray_minimap(t_config *config, float cos_angle,
					float sin_angle);
void			compute_minimap(t_config *config);
void			compute_map_dims(t_config *config);

/* --- PLAYER --- */
double			get_initial_angle(char dir);
bool			is_walkable(t_config *config, float x, float y);
bool			is_walkable_radius(t_config *config, float x, float y);
void			update_player_movement(t_config *config, double delta_time);
void			update_player_rotation_keys(t_config *config,
					double delta_time);
void			draw_player_ray_cone(t_config *config);
double			get_delta_time(void);

/* --- COLOR --- */
uint32_t		get_color_value(t_color color);

/* --- FREE --- */
void			free_partial_map(char **map, int count);
void			free_split(char **split);
int				error_msg(char *msg);
void			free_config(t_config **config);
void			free_mlx(t_config *config);

#endif
