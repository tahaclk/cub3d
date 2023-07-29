/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_rotations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcelik <tcelik@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 18:01:16 by tcelik            #+#    #+#             */
/*   Updated: 2023/07/29 18:01:18 by tcelik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	vals->player.dir_y = old_dir_x * sin(-vals->player.rot_speed)
		+ vals->player.dir_y * cos(-vals->player.rot_speed);
	vals->player.plane_x = vals->player.plane_x * cos(-vals->player.rot_speed)
		- vals->player.plane_y * sin(-vals->player.rot_speed);
	vals->player.plane_y = old_plane_x * sin(-vals->player.rot_speed)
		+ vals->player.plane_y * cos(-vals->player.rot_speed);
}

void	rotate_right(t_cub3d *vals)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = vals->player.dir_x;
	old_plane_x = vals->player.plane_x;
	vals->player.dir_x = vals->player.dir_x * cos(vals->player.rot_speed)
		- vals->player.dir_y * sin(vals->player.rot_speed);
	vals->player.dir_y = old_dir_x * sin(vals->player.rot_speed)
		+ vals->player.dir_y * cos(vals->player.rot_speed);
	vals->player.plane_x = vals->player.plane_x * cos(vals->player.rot_speed)
		- vals->player.plane_y * sin(vals->player.rot_speed);
	vals->player.plane_y = old_plane_x * sin(vals->player.rot_speed)
		+ vals->player.plane_y * cos(vals->player.rot_speed);
}
