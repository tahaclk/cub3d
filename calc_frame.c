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

void	calc_frame_init(t_cub3d *vals)
{
	vals->camera_x = 2 * vals->x / (double) WIDTH - 1;
	vals->ray_dir_x = vals->player.dir_x + vals->player.plane_x
		* vals->camera_x;
	vals->ray_dir_y = vals->player.dir_y + vals->player.plane_y
		* vals->camera_x;
	vals->map_x = (int) vals->player.x;
	vals->map_y = (int) vals->player.y;
	if (vals->ray_dir_x == 0)
		vals->delta_dist_x = 1e30;
	else
		vals->delta_dist_x = fabs(1 / vals->ray_dir_x);
	if (vals->ray_dir_y == 0)
		vals->delta_dist_y = 1e30;
	else
		vals->delta_dist_y = fabs(1 / vals->ray_dir_y);
	vals->hit = 0;
}

void	calc_side_dist(t_cub3d *vals)
{
	if (vals->ray_dir_x < 0)
	{
		vals->step_x = -1;
		vals->side_dist_x = (vals->player.x - vals->map_x) * vals->delta_dist_x;
	}
	else
	{
		vals->step_x = 1;
		vals->side_dist_x = (vals->map_x + 1.0 - vals->player.x)
			* vals->delta_dist_x;
	}
	if (vals->ray_dir_y < 0)
	{
		vals->step_y = -1;
		vals->side_dist_y = (vals->player.y - vals->map_y) * vals->delta_dist_y;
	}
	else
	{
		vals->step_y = 1;
		vals->side_dist_y = (vals->map_y + 1.0 - vals->player.y)
			* vals->delta_dist_y;
	}
}

void	calc_wall_height(t_cub3d *vals)
{
	while (vals->hit == 0)
	{
		if (vals->side_dist_x < vals->side_dist_y)
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
		if (vals->map[vals->map_y][vals->map_x] > 0)
			vals->hit = 1;
	}
	if (vals->side == 0)
		vals->perp_wall_dist = (vals->side_dist_x - vals->delta_dist_x);
	else
		vals->perp_wall_dist = (vals->side_dist_y - vals->delta_dist_y);
	vals->line_height = (int)(HEIGHT / vals->perp_wall_dist);
}

void	calc_wall_x(t_cub3d *vals)
{
	vals->draw_start = -vals->line_height / 2 + HEIGHT / 2;
	if (vals->draw_start < 0)
		vals->draw_start = 0;
	vals->draw_end = vals->line_height / 2 + HEIGHT / 2;
	if (vals->draw_end >= HEIGHT)
		vals->draw_end = HEIGHT - 1;
	if (vals->side == 0)
		vals->wall_x = vals->player.y + vals->perp_wall_dist * vals->ray_dir_y;
	else
		vals->wall_x = vals->player.x + vals->perp_wall_dist * vals->ray_dir_x;
	vals->wall_x -= floor(vals->wall_x);
}

void	calc_frame(t_cub3d *vals)
{
	vals->x = -1;
	mlx_clear_window(vals->mlx, vals->img.win);
	while (++(vals->x) < WIDTH)
	{
		calc_frame_init(vals);
		calc_side_dist(vals);
		calc_wall_height(vals);
		calc_wall_x(vals);
		vals->tex_x = (int)(vals->wall_x * (double) TEX_W);
		vals->step = 1.0 * TEX_H / vals->line_height;
		vals->tex_pos = (vals->draw_start - HEIGHT / 2 + vals->line_height / 2)
			* vals->step;
		vals->y = -1;
		while (++vals->y < HEIGHT)
			calc_texture_pixel_color(vals);
	}
}
