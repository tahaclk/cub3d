/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_move.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcelik <tcelik@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 18:00:01 by tcelik            #+#    #+#             */
/*   Updated: 2023/07/29 18:00:02 by tcelik           ###   ########.fr       */
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
