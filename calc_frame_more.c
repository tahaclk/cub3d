/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_frame_more.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcelik <tcelik@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 19:25:18 by tcelik            #+#    #+#             */
/*   Updated: 2023/07/29 19:25:19 by tcelik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_pause(t_cub3d *vals)
{
	int	i;
	int	j;

	i = 3 * WIDTH / 8 - 1;
	while (++i < (15 * WIDTH) / 32)
	{
		j = HEIGHT / 3 - 1;
		while (++j < (2 * HEIGHT) / 3)
			put_px_img(vals, i, j, create_trgb(50, 255, 255, 255));
	}
	i = (17 * WIDTH) / 32 - 1;
	while (++i < (5 * WIDTH) / 8)
	{
		j = HEIGHT / 3 - 1;
		while (++j < (2 * HEIGHT) / 3)
			put_px_img(vals, i, j, create_trgb(50, 255, 255, 255));
	}
	mlx_put_image_to_window(vals->mlx, vals->img.win, vals->img.image, 0, 0);
}

void	print_player(t_cub3d *vals, int x, int y, double scale)
{
	int	i;
	int	j;

	i = -2;
	j = -2;
	while (++i < 2)
	{
		j = -2;
		while (++j < 2)
			put_px_img(vals, (int)(vals->player.x
					* ((WIDTH / scale) / (double) vals->map_wd) + x + i),
				(int)(vals->player.y * ((HEIGHT / scale)
						/ (double) vals->map_he) + y + j),
				create_trgb(0, 255, 0, 0));
	}
}

void	print_mini_map(t_cub3d *vals)
{
	int		mini_x;
	int		mini_y;

	vals->x = WIDTH / 100;
	vals->y = HEIGHT / 100;
	vals->scale = 4.0;
	mini_x = -1;
	while ((int)(++mini_x / ((WIDTH / vals->scale)
			/ (double) vals->map_wd)) < vals->map_wd)
	{
		mini_y = -1;
		while ((int)(++mini_y / ((HEIGHT / vals->scale)
				/ (double) vals->map_he)) < vals->map_he)
		{
			if (vals->map[(int)(mini_y / ((HEIGHT / vals->scale) / (double)
						vals->map_he))][(int)(mini_x / ((WIDTH / vals->scale)
					/ (double) vals->map_wd))] == 1)
				put_px_img(vals, mini_x + vals->x, mini_y + vals->y,
					create_trgb(0, 190, 190, 190));
			else
				put_px_img(vals, mini_x + vals->x, mini_y + vals->y,
					create_trgb(0, 90, 90, 90));
		}
	}
}

void	calc_texture_pixel_color(t_cub3d *vals)
{
	int	color;
	int	tex_y;

	if (vals->y < vals->draw_start)
		put_px_img(vals, vals->x, vals->y, create_trgb(0, vals->sky.r,
				vals->sky.g, vals->sky.b));
	else if (vals->y >= vals->draw_start && vals->y <= vals->draw_end)
	{
		tex_y = (int) vals->tex_pos & (TEX_H - 1);
		vals->tex_pos += vals->step;
		if (vals->side == 0 && vals->ray_dir_x > 0)
			color = get_pixel_in_tex(vals->north, vals->tex_x, tex_y);
		else if (vals->side == 0 && vals->ray_dir_x < 0)
			color = get_pixel_in_tex(vals->south, vals->tex_x, tex_y);
		else if (vals->side == 1 && vals->ray_dir_y > 0)
			color = get_pixel_in_tex(vals->west, vals->tex_x, tex_y);
		else if (vals->side == 1 && vals->ray_dir_y < 0)
			color = get_pixel_in_tex(vals->east, vals->tex_x, tex_y);
		put_px_img(vals, vals->x, vals->y, color);
	}
	else
		put_px_img(vals, vals->x, vals->y, create_trgb(0, vals->floor.r,
				vals->floor.g, vals->floor.b));
}
