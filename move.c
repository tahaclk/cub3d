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
	if (key_code == 35)
	{
		draw_pause(vals);
		vals->lock = !vals->lock;
	}
	if (vals->lock == 0)
	{
		mlx_mouse_hide();
		mlx_mouse_move(vals->img.win, WIDTH / 2, HEIGHT / 2);
	}
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

void	move(t_cub3d *vals)
{
	if (vals->moves[0] == 1)
		move_forward(vals);
	else if (vals->moves[1] == 1)
		move_back(vals);
	if (vals->moves[2] == 1)
		move_left(vals);
	else if (vals->moves[3] == 1)
		move_right(vals);
	if (vals->moves[4] == 1)
		rotate_left(vals);
	else if (vals->moves[5] == 1)
		rotate_right(vals);
}
