/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcelik <tcelik@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 13:21:37 by tcelik            #+#    #+#             */
/*   Updated: 2023/07/21 13:21:39 by tcelik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_textures(t_cub3d *vals)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (vals->c_map[i] && counter < 6)
	{
		if (ft_strlen(vals->c_map[i]) > 3)
			counter += take_data(vals, i);
		i++;
	}
	if (counter == 6 && vals->c_map[i])
		return (i);
	else
		return (-1);
}

void	init_img(t_cub3d *f)
{
	int		bpp;
	int		sizeline;
	int		endian;

	f->img.image = mlx_new_image(f->img.mlx, WIDTH, HEIGHT);
	f->img.data = mlx_get_data_addr(f->img.image, &bpp, &sizeline, &endian);
	f->img.bpp = bpp;
	f->img.sizeline = sizeline;
	f->img.endian = endian;
}

void	init_vals(t_cub3d *vals)
{
	vals->img.mlx = mlx_init();
	vals->img.win = mlx_new_window(vals->img.mlx, WIDTH, HEIGHT, "Cub3d");
	init_img(vals);
	vals->player.move_speed = 0.03;
	vals->player.rot_speed = 0.02;
	vals->moves[0] = 0;
	vals->moves[1] = 0;
	vals->moves[2] = 0;
	vals->moves[3] = 0;
	vals->moves[4] = 0;
	vals->moves[5] = 0;
}

void	init_map(t_cub3d *vals, char **av)
{
	int	fd;
	int	map_start_index;

	fd = open_file(vals, av);
	vals->c_map = read_file(vals, fd);
	map_start_index = init_textures(vals);
	init_map_data(vals, &map_start_index);
	map_char_to_int(vals);
}
