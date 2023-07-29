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

void	open_tex_file(t_cub3d *vals)
{
	vals->north.image = mlx_xpm_file_to_image(vals->mlx, vals->north.path, &(vals->north.w), &(vals->north.h));
	vals->south.image = mlx_xpm_file_to_image(vals->mlx, vals->south.path, &(vals->south.w), &(vals->south.h));
	vals->west.image = mlx_xpm_file_to_image(vals->mlx, vals->west.path, &(vals->west.w), &(vals->west.h));
	vals->east.image = mlx_xpm_file_to_image(vals->mlx, vals->east.path, &(vals->east.w), &(vals->east.h));
	if (!vals->north.image || !vals->south.image || !vals->west.image || !vals->east.image)
		free_tex_image("ERROR\nTexture file name is wrong!\n", vals);
	vals->north.data = mlx_get_data_addr(vals->north.image, &(vals->north.bpp), &(vals->north.sizeline), &(vals->north.endian));
	vals->south.data = mlx_get_data_addr(vals->south.image, &(vals->south.bpp), &(vals->south.sizeline), &(vals->south.endian));
	vals->west.data = mlx_get_data_addr(vals->west.image, &(vals->west.bpp), &(vals->west.sizeline), &(vals->west.endian));
	vals->east.data = mlx_get_data_addr(vals->east.image, &(vals->east.bpp), &(vals->east.sizeline), &(vals->east.endian));
}

int	init_textures(t_cub3d *vals)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (vals->c_map[i] && counter < 6)
	{
		if (ft_strlen(vals->c_map[i]) > 3)
		{
			counter += take_data(vals, i);
		}
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

	f->img.image = mlx_new_image(f->mlx, WIDTH, HEIGHT);
	f->img.data = mlx_get_data_addr(f->img.image, &bpp, &sizeline, &endian);
	f->img.bpp = bpp;
	f->img.sizeline = sizeline;
	f->img.endian = endian;
}

void	init_vals(t_cub3d *vals)
{
	vals->mlx = mlx_init();
	vals->img.win = mlx_new_window(vals->mlx, WIDTH, HEIGHT, "Cub3D");
	init_img(vals);
	vals->north.path = NULL;
	vals->south.path = NULL;
	vals->west.path = NULL;
	vals->east.path = NULL;
	vals->player.move_speed = 0.06;
	vals->player.rot_speed = 0.04;
	vals->moves[0] = 0;
	vals->moves[1] = 0;
	vals->moves[2] = 0;
	vals->moves[3] = 0;
	vals->moves[4] = 0;
	vals->moves[5] = 0;
	vals->moves[6] = 0;
	vals->moves[7] = 0;
	vals->lock = 0;
	vals->m_old_pos_x = WIDTH / 2;
	vals->m_old_pos_y = HEIGHT / 2;
	vals->m_pos_x = WIDTH / 2;
	vals->m_pos_y = HEIGHT / 2;
	mlx_mouse_move(vals->img.win, WIDTH / 2, HEIGHT / 2);
	mlx_mouse_hide();
}

void	init_map(t_cub3d *vals, char **av)
{
	int	fd;
	int	map_start_index;

	fd = open_file(vals, av);
	vals->c_map = read_file(vals, fd);
	map_start_index = init_textures(vals);
	open_tex_file(vals);
	init_map_data(vals, &map_start_index);
	check_split_map(vals, av);
	map_char_to_int(vals);
}
