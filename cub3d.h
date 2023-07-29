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
# define WIDTH 800
# define HEIGHT 600
# define TEX_W 64
# define TEX_H 64
# define PI 3.141592653589793

typedef struct s_image
{
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
	char	*data;
	void	*mlx;
	void	*win;
	void	*image;
	int		bpp;
	int		sizeline;
	int		endian;
	int		w;
	int		h;
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
	void		*mlx;
	char		**c_map;
	int			**map;
	int			moves[8];
	int			map_wd;
	int			map_he;
	int			map_x;
	int			map_y;
	int			step_x;
	int			step_y;
	int			hit;
	int			side;
	int			line_height;
	int			draw_start;
	int			draw_end;
	int			m_old_pos_x;
	int			m_old_pos_y;
	int			m_pos_x;
	int			m_pos_y;
	int			lock;
	int			x;
	int			y;
	double		step;
	double		tex_x;
	double		tex_pos;
	double		scale;
	double		wall_x;
	double		camera_x;
	double		ray_dir_x;
	double		ray_dir_y;
	double		side_dist_x;
	double		side_dist_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		perp_wall_dist;
}	t_cub3d;

void			init_vals(t_cub3d *vals);
void			init_img(t_cub3d *f);
void			init_map(t_cub3d *vals, char **av);
void			init_map_data(t_cub3d *vals, int *idx);
int				init_textures(t_cub3d *vals);
int				key(int keycode, t_cub3d *vals);
int				closee(int keycode, t_cub3d *vals);
int				open_file(t_cub3d *vals, char **av);
char			**read_file(t_cub3d *vals, int fd);
int				take_data(t_cub3d *vals, int i);
int				take_tx_path(t_cub3d *vals, int i, char *key, char **path);
int				take_color(t_cub3d *vals, int i, char *key, t_color *color);
void			msg_fail_exit(char *msg, t_cub3d *vals, int exit_status);
void			check_color_depth(t_cub3d *vals, t_color *color);
int				fill_color(t_cub3d *vals, t_color *color, char *str);
int				find_longest_line(t_cub3d *vals, int i);
int				is_map_char(int c);
int				is_all_digit(char **clr);
void			double_free(char **vals);
char			**double_malloc(t_cub3d *vals, int line_count,
					int max_line_size);
void			check_map(t_cub3d *vals, int map_start_idx, char **map);
void			check_map_chars(t_cub3d *vals);
void			check_split_map(t_cub3d *vals, char **av);
int				is_user_zero(int c);
int				is_user_char(int c);
int				check_player(t_cub3d *vals, char **map, int i, int j);
void			map_char_to_int(t_cub3d *vals);
void			fill_player_dir(t_cub3d *vals, double x, double y);
void			fill_int_val(t_cub3d *vals, int i, int j);
void			fill_int_map(t_cub3d *vals);
void			calc_frame(t_cub3d *vals);
void			put_px_img(t_cub3d *f, int x, int y, int color);
int				create_trgb(int t, int r, int g, int b);
int				key_press(int key_code, t_cub3d *vals);
int				key_release(int key_code, t_cub3d *vals);
void			move(t_cub3d *vals);
void			move_forward(t_cub3d *vals);
void			move_back(t_cub3d *vals);
void			move_left(t_cub3d *vals);
void			move_right(t_cub3d *vals);
void			rotate_left(t_cub3d *vals);
void			rotate_right(t_cub3d *vals);
unsigned int	get_pixel_in_tex(t_texture tex, int x, int y);
void			rotate_with_mouse(t_cub3d *vals);
void			free_tex_paths(char *msg, t_cub3d *vals, int exit_status);
void			free_tex_paths_2(char *msg, t_cub3d *vals, int exit_status);
void			free_tex_image(char *msg, t_cub3d *vals);
void			free_tex_image2(char *msg, t_cub3d *vals, int exit_status);
void			free_map(t_cub3d *vals, char **map, char *msg);
int				red_x_close(int keycode, t_cub3d *vals);
void			draw_pause(t_cub3d *vals);
void			check_6(t_cub3d *vals, char *str, int fd);
int				check_6_after(t_cub3d *vals, char *str, int i, int fd);
int				check_after_newl(t_cub3d *vals, char *str, int i, int fd);
void			print_player(t_cub3d *vals, int x, int y, double scale);
void			print_mini_map(t_cub3d *vals);
void			calc_texture_pixel_color(t_cub3d *vals);
void			calc_wall_x(t_cub3d *vals);
void			calc_wall_height(t_cub3d *vals);
void			calc_side_dist(t_cub3d *vals);
void			acalc_frame_init(t_cub3d *vals);
#endif
