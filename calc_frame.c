/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_frame.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcelik <tcelik@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 12:08:44 by tcelik            #+#    #+#             */
/*   Updated: 2023/07/25 12:08:45 by tcelik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_mini_map(t_cub3d *vals)
{
	int	mini_map_x;
	int	mini_map_y;
	int	x;
	int	y;
	double	scale;

	x = WIDTH / 100;
	y = HEIGHT / 100;
	mini_map_x = 0;
	scale = 4.0;
	while ((int)(mini_map_x / ((WIDTH / scale) / (double) vals->map_width)) < vals->map_width)
	{
		mini_map_y = 0;
		while ((int)(mini_map_y / ((HEIGHT / scale) / (double) vals->map_height)) < vals->map_height)
		{
			if (vals->map[(int)(mini_map_y / ((HEIGHT / scale) / (double) vals->map_height))][(int) (mini_map_x / ((WIDTH / scale) / (double) vals->map_width))] == 1)
				put_pixel_in_img(vals, mini_map_x + x, mini_map_y + y, create_trgb(0, 190, 190, 190));
			else
				put_pixel_in_img(vals, mini_map_x + x, mini_map_y + y, create_trgb(0, 90, 90, 90));
			mini_map_y++;
		}
		mini_map_x++;
	}

	int i = -2;
	int	j = -2;
	while (++i < 2)
	{
		j = -2;
		while (++j < 2)
			put_pixel_in_img(vals, (int)(vals->player.x * ((WIDTH / scale) / (double) vals->map_width) + x + i), (int)(vals->player.y * ((HEIGHT / scale) / (double) vals->map_height) + y + j), create_trgb(0, 255, 0, 0));
	}
}

void	calc_frame(t_cub3d *vals)
{
	int	x;

	x = -1;
	mlx_clear_window(vals->mlx, vals->img.win);
	while (++x < WIDTH)
	{
		vals->camera_x = 2 * x / (double) WIDTH - 1;
		vals->ray_dir_x = vals->player.dir_x + vals->player.plane_x * vals->camera_x;
		vals->ray_dir_y = vals->player.dir_y + vals->player.plane_y * vals->camera_x;
		vals->map_x = (int) vals->player.x;
		vals->map_y = (int) vals->player.y;
		vals->delta_dist_x = (vals->ray_dir_x == 0) ? 1e30 : fabs(1 / vals->ray_dir_x);
		vals->delta_dist_y = (vals->ray_dir_y == 0) ? 1e30 : fabs(1 / vals->ray_dir_y);
		vals->hit = 0;
		if (vals->ray_dir_x < 0)
		{
			vals->step_x = -1;
			vals->side_dist_x = (vals->player.x - vals->map_x) * vals->delta_dist_x;
		}
		else
		{
			vals->step_x = 1;
			vals->side_dist_x = (vals->map_x + 1.0 - vals->player.x) * vals->delta_dist_x;
		}
		if (vals->ray_dir_y < 0)
		{
			vals->step_y = -1;
			vals->side_dist_y = (vals->player.y - vals->map_y) * vals->delta_dist_y;
		}
		else
		{
			vals->step_y = 1;
			vals->side_dist_y = (vals->map_y + 1.0 - vals->player.y) * vals->delta_dist_y;
		}

		while(vals->hit == 0)
		{
			if(vals->side_dist_x < vals->side_dist_y)
			{
				vals->side_dist_x += vals->delta_dist_x;
				vals->map_x += vals->step_x;
				vals->side = 0;
			}
			else
			{
				vals->side_dist_y += vals->delta_dist_y;
				vals->map_y += vals->step_y;
				vals->side = 1;
			}
			if(vals->map[vals->map_y][vals->map_x] > 0)
				vals->hit = 1;
		}
		if(vals->side == 0)
			vals->perp_wall_dist = (vals->side_dist_x - vals->delta_dist_x);
		else
			vals->perp_wall_dist = (vals->side_dist_y - vals->delta_dist_y);

		vals->line_height = (int) (HEIGHT / vals->perp_wall_dist);


		vals->draw_start = -vals->line_height / 2 + HEIGHT / 2;
		if (vals->draw_start < 0)
			vals->draw_start = 0;
		vals->draw_end = vals->line_height / 2 + HEIGHT / 2;
		if (vals->draw_end >= HEIGHT)
			vals->draw_end = HEIGHT - 1;

		int	texNum = vals->map[vals->map_y][vals->map_y] - 1;

		double	wall_x;

		if (vals->side == 0)
			wall_x = vals->player.y + vals->perp_wall_dist * vals->ray_dir_y;
		else
			wall_x = vals->player.x + vals->perp_wall_dist * vals->ray_dir_x;
		wall_x -= floor(wall_x);

		int	tex_x = (int) (wall_x * (double) TEX_W);
		/* if (vals->side == 0 && vals->ray_dir_x > 0)
			tex_x = TEX_W - tex_x - 1;
		if (vals->side == 1 && vals->ray_dir_x < 0)
			tex_x = TEX_W - tex_x - 1; */

		double	step = 1.0 * TEX_H / vals->line_height;

		double	tex_pos = (vals->draw_start - HEIGHT / 2 + vals->line_height / 2) * step;
		int y = -1;
		while (++y < HEIGHT)
		{
			if (y < vals->draw_start)
				put_pixel_in_img(vals, x, y, create_trgb(0, vals->sky.r, vals->sky.g, vals->sky.b));
			else if (y >= vals->draw_start && y <= vals->draw_end)
			{
				int color;
				int	tex_y = (int) tex_pos & (TEX_H - 1);
				tex_pos += step;
				if (vals->side == 0 && vals->ray_dir_x > 0)
					color = get_pixel_in_tex(vals->north, tex_x, tex_y);
				else if (vals->side == 0 && vals->ray_dir_x < 0)
					color = get_pixel_in_tex(vals->south, tex_x, tex_y);
				else if (vals->side == 1 && vals->ray_dir_y > 0)
					color = get_pixel_in_tex(vals->west, tex_x, tex_y);
				else if (vals->side == 1 && vals->ray_dir_y < 0)
					color = get_pixel_in_tex(vals->east, tex_x, tex_y);
				put_pixel_in_img(vals, x, y, color);
			}
			else
				put_pixel_in_img(vals, x, y, create_trgb(0, vals->floor.r, vals->floor.g, vals->floor.b));
		}
	}
	print_mini_map(vals);
	mlx_put_image_to_window(vals->mlx, vals->img.win, vals->img.image, 0, 0);
}
