/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcelik <tcelik@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 13:21:09 by tcelik            #+#    #+#             */
/*   Updated: 2023/07/21 13:21:12 by tcelik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_loop(t_cub3d *vals)
{
	if (vals->lock)
	{
		mlx_mouse_show();
		return (0);
	}
	if ((vals->moves[0] || vals->moves[1]) && (vals->moves[2] || vals->moves[3]))
		vals->player.move_speed = 0.06 / sqrt(2);
	else
		vals->player.move_speed = 0.06;
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
	mlx_mouse_get_pos(vals->img.win, &(vals->m_pos_x), &(vals->m_pos_y));
	if (vals->m_pos_x - vals->m_old_pos_x != 0)
		rotate_with_mouse(vals);
	mlx_mouse_move(vals->img.win, WIDTH / 2, HEIGHT / 2);
	vals->m_old_pos_x = WIDTH / 2;
	vals->m_old_pos_y = HEIGHT / 2;
	vals->m_pos_x = WIDTH / 2;
	vals->m_pos_y = HEIGHT / 2;
	calc_frame(vals);
	return (0);
}

int	main(int ac, char **av)
{
	t_cub3d	vals;

	if (ac == 2)
	{
		init_vals(&vals);
		init_map(&vals, av);
		mlx_hook(vals.img.win, 2, 0, key_press, &vals);
		mlx_hook(vals.img.win, 3, 0, key_release, &vals);
		mlx_hook(vals.img.win, 17, 1L << 2, red_x_close, &vals);
		mlx_loop_hook(vals.mlx, &ft_loop, &vals);
		mlx_loop(vals.mlx);
	}
	else
	{
		printf("ERROR\nPlease write map name!!\n");
		return (1);
	}
	return (0);
}
