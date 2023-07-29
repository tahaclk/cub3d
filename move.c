/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcelik <tcelik@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 18:05:22 by tcelik            #+#    #+#             */
/*   Updated: 2023/07/25 18:05:24 by tcelik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_forward(t_cub3d *vals)
{
	if (vals->map[(int)vals->player.y][(int)(vals->player.x
		+ vals->player.dir_x * vals->player.move_speed)] == 0)
		vals->player.x += vals->player.dir_x * vals->player.move_speed;
	if (vals->map[(int)(vals->player.y + vals->player.dir_y
			* vals->player.move_speed)][(int)(vals->player.x)] == 0)
		vals->player.y += vals->player.dir_y * vals->player.move_speed;
}

void	move_back(t_cub3d *vals)
{
	if (vals->map[(int)vals->player.y][(int)(vals->player.x
		- vals->player.dir_x * vals->player.move_speed)] == 0)
		vals->player.x -= vals->player.dir_x * vals->player.move_speed;
	if (vals->map[(int)(vals->player.y - vals->player.dir_y
			* vals->player.move_speed)][(int)(vals->player.x)] == 0)
		vals->player.y -= vals->player.dir_y * vals->player.move_speed;
}

void	move_left(t_cub3d *vals)
{
	if (vals->map[(int)vals->player.y][(int)(vals->player.x + vals->player.dir_y
		* vals->player.move_speed)] == 0)
		vals->player.x += vals->player.dir_y * vals->player.move_speed;
	if (vals->map[(int)(vals->player.y - vals->player.dir_x
			* vals->player.move_speed)][(int)(vals->player.x)] == 0)
		vals->player.y += -vals->player.dir_x * vals->player.move_speed;
}

void	move_right(t_cub3d *vals)
{
	if (vals->map[(int)vals->player.y][(int)(vals->player.x - vals->player.dir_y
		* vals->player.move_speed)] == 0)
		vals->player.x -= vals->player.dir_y * vals->player.move_speed;
	if (vals->map[(int)(vals->player.y + vals->player.dir_x
			* vals->player.move_speed)][(int)(vals->player.x)] == 0)
		vals->player.y -= -vals->player.dir_x * vals->player.move_speed;
}

void	rotate_with_mouse(t_cub3d *vals)
{
	double	old_dir_x;
	double	old_plane_x;
	double	rot_x;

	if (vals->m_pos_x - vals->m_old_pos_x > 0)
		rot_x = vals->player.rot_speed * ((vals->m_pos_x
					- vals->m_old_pos_x) / 10);
	else
		rot_x = vals->player.rot_speed * ((vals->m_pos_x
					- vals->m_old_pos_x) / 10);
	old_dir_x = vals->player.dir_x;
	old_plane_x = vals->player.plane_x;
	vals->player.dir_x = vals->player.dir_x * cos(rot_x) - vals->player.dir_y
		* sin(rot_x);
	vals->player.dir_y = old_dir_x * sin(rot_x) + vals->player.dir_y
		* cos(rot_x);
	vals->player.plane_x = vals->player.plane_x * cos(rot_x)
		- vals->player.plane_y * sin(rot_x);
	vals->player.plane_y = old_plane_x * sin(rot_x) + vals->player.plane_y
		* cos(rot_x);
}

void	rotate_left(t_cub3d *vals)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = vals->player.dir_x;
	old_plane_x = vals->player.plane_x;
	vals->player.dir_x = vals->player.dir_x * cos(-vals->player.rot_speed)
		- vals->player.dir_y * sin(-vals->player.rot_speed);
	vals->player.dir_y = old_dir_x * sin(-vals->player.rot_speed) +
		vals->player.dir_y * cos(-vals->player.rot_speed);
	vals->player.plane_x = vals->player.plane_x * cos(-vals->player.rot_speed)
		- vals->player.plane_y * sin(-vals->player.rot_speed);
	vals->player.plane_y = old_plane_x * sin(-vals->player.rot_speed) +
		vals->player.plane_y * cos(-vals->player.rot_speed);
}

void	rotate_right(t_cub3d *vals)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = vals->player.dir_x;
	old_plane_x = vals->player.plane_x;
	vals->player.dir_x = vals->player.dir_x * cos(vals->player.rot_speed) -
		vals->player.dir_y * sin(vals->player.rot_speed);
	vals->player.dir_y = old_dir_x * sin(vals->player.rot_speed) +
		vals->player.dir_y * cos(vals->player.rot_speed);
	vals->player.plane_x = vals->player.plane_x * cos(vals->player.rot_speed) -
		vals->player.plane_y * sin(vals->player.rot_speed);
	vals->player.plane_y = old_plane_x * sin(vals->player.rot_speed) +
		vals->player.plane_y * cos(vals->player.rot_speed);
}

int	key_press(int key_code, t_cub3d *vals)
{
	if (key_code == 13)
		vals->moves[0] = 1;
	else if (key_code == 1)
		vals->moves[1] = 1;
	else if (key_code == 0)
		vals->moves[2] = 1;
	else if (key_code == 2)
		vals->moves[3] = 1;
	else if (key_code == 123)
		vals->moves[4] = 1;
	else if (key_code == 124)
		vals->moves[5] = 1;
	else if (key_code == 53)
		closee(key_code, vals);
	return (0);
}

int	key_release(int key_code, t_cub3d *vals)
{
	if (key_code == 13)
		vals->moves[0] = 0;
	else if (key_code == 1)
		vals->moves[1] = 0;
	else if (key_code == 0)
		vals->moves[2] = 0;
	else if (key_code == 2)
		vals->moves[3] = 0;
	else if (key_code == 123)
		vals->moves[4] = 0;
	else if (key_code == 124)
		vals->moves[5] = 0;
	return (0);
}
