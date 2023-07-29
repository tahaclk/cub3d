/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcelik <tcelik@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 17:03:56 by tcelik            #+#    #+#             */
/*   Updated: 2023/07/28 17:03:57 by tcelik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_tex_paths_2(char *msg, t_cub3d *vals, int exit_status)
{
	double_free(vals->c_map);
	if (vals->north.path)
		free(vals->north.path);
	if (vals->south.path)
		free(vals->south.path);
	if (vals->west.path)
		free(vals->west.path);
	if (vals->east.path)
		free(vals->east.path);
	msg_fail_exit(msg, vals, exit_status);
}

void	free_tex_paths(char *msg, t_cub3d *vals, int exit_status)
{
	if (vals->north.path)
		free(vals->north.path);
	if (vals->south.path)
		free(vals->south.path);
	if (vals->west.path)
		free(vals->west.path);
	if (vals->east.path)
		free(vals->east.path);
	msg_fail_exit(msg, vals, exit_status);
}

void	free_tex_image(char *msg, t_cub3d *vals)
{
	double_free(vals->c_map);
	if (vals->north.image)
		mlx_destroy_image(vals->mlx, vals->north.image);
	if (vals->south.image)
		mlx_destroy_image(vals->mlx, vals->south.image);
	if (vals->west.image)
		mlx_destroy_image(vals->mlx, vals->west.image);
	if (vals->east.image)
		mlx_destroy_image(vals->mlx, vals->east.image);
	free_tex_paths(msg, vals, EXIT_FAILURE);
}

void	free_tex_image2(char *msg, t_cub3d *vals, int exit_status)
{
	if (vals->north.image)
		mlx_destroy_image(vals->mlx, vals->north.image);
	if (vals->south.image)
		mlx_destroy_image(vals->mlx, vals->south.image);
	if (vals->west.image)
		mlx_destroy_image(vals->mlx, vals->west.image);
	if (vals->east.image)
		mlx_destroy_image(vals->mlx, vals->east.image);
	free_tex_paths(msg, vals, exit_status);
}

void	free_map(t_cub3d *vals, char **map, char *msg)
{
	double_free(map);
	free_tex_image(msg, vals);
}
