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
	if ((vals->moves[0] || vals->moves[1]) && (vals->moves[2] || vals->moves[3]))
		vals->player.move_speed = 0.03 / sqrt(2);
	else
		vals->player.move_speed = 0.03;
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
	calc_frame(vals);
	return (0);
}

int	main(int ac, char **av)
{
	t_cub3d	vals;

	if (ac == 2)
	{
		init_map(&vals, av);
		init_vals(&vals);
		mlx_hook(vals.img.win, 2, 0, key_press, &vals);
		mlx_hook(vals.img.win, 3, 1, key_release, &vals);
		mlx_hook(vals.img.win, 17, 1L << 2, closee, &vals);
		mlx_loop_hook(vals.img.mlx, &ft_loop, &vals);
		mlx_loop(vals.img.mlx);
	}
	else
		msg_fail_exit("Please write map name!!\n");
	return (0);
}
