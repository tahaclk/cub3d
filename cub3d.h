/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcelik <tcelik@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 13:02:06 by tcelik            #+#    #+#             */
/*   Updated: 2023/07/21 13:02:19 by tcelik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <math.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include "mlxlib/mlx.h"
# include "gnl/get_next_line.h"
# include "libft/libft.h"
# define WIDTH 1280
# define HEIGHT 720
# define PI 3.141592653589793

enum {
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};

typedef struct s_image
{
	void	*mlx;
	void	*win;
	int		*image;
	char	*data;
	int		bpp;
	int		sizeline;
	int		endian;
}	t_image;

typedef struct s_player
{
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	move_speed;
	double	rot_speed;
}	t_player;

typedef struct s_color
{
	int		r;
	int		g;
	int		b;
}	t_color;

typedef struct s_texture
{
	char	*path;
}	t_texture;

typedef struct s_cub3d
{
	t_image		img;
	t_player	player;
	t_texture	north;
	t_texture	south;
	t_texture	west;
	t_texture	east;
	t_color		sky;
	t_color		floor;
	char		**c_map;
	int			**map;
	int			moves[6];
	int			map_width;
	int			map_height;
	int			map_x;
	int			map_y;
	int			step_x;
	int			step_y;
	int			hit;
	int			side;
	int			line_height;
	int			draw_start;
	int			draw_end;
	double		camera_x;
	double		ray_dir_x;
	double		ray_dir_y;
	double		side_dist_x;
	double		side_dist_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		perpWallDist;
}	t_cub3d;

void	init_vals(t_cub3d *vals);
void	init_img(t_cub3d *f);
void	init_map(t_cub3d *vals, char **av);
void	init_map_data(t_cub3d *vals, int *idx);
int		init_textures(t_cub3d *vals);
int		key(int keycode, t_cub3d *vals);
int		closee(int keycode, t_cub3d *vars);
void	free_exit(t_cub3d *vals);
int		open_file(t_cub3d *vals, char **av);
char	**read_file(t_cub3d *vals, int fd);
int		take_data(t_cub3d *vals, int i);
int		take_tx_path(t_cub3d *vals, int i, char *key, char **path);
int		take_color(t_cub3d *vals, int i, char *key, t_color *color);
void	msg_fail_exit(char *msg);
void	check_color_depth(t_cub3d *vals, t_color *color);
int		fill_color(t_cub3d *vals, t_color *color, char *str);
int		find_longest_line(t_cub3d *vals, int i);
int		is_map_char(int c);
void	double_free(char **vals);
char	**double_malloc(t_cub3d *vals, int line_count, int max_line_size);
void	check_map(t_cub3d *vals, int map_start_idx, char **map);
void	check_map_chars(t_cub3d *vals);
int		is_user_zero(int c);
int		is_user_char(int c);
int		check_player(t_cub3d *vals, char **map, int i, int j);
void	map_char_to_int(t_cub3d *vals);
void	fill_player_dir(t_cub3d *vals, double x, double y);
void	fill_int_val(t_cub3d *vals, int i, int j);
void	fill_int_map(t_cub3d *vals);
void	calc_frame(t_cub3d *vals);
void	put_pixel_in_img(t_cub3d *f, int x, int y, int color);
int		create_trgb(int t, int r, int g, int b);
int		key_press(int key_code, t_cub3d *vals);
int		key_release(int key_code, t_cub3d *vals);
void	move_forward(t_cub3d *vals);
void	move_back(t_cub3d *vals);
void	move_left(t_cub3d *vals);
void	move_right(t_cub3d *vals);
void	rotate_left(t_cub3d *vals);
void	rotate_right(t_cub3d *vals);
#endif