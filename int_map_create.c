/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_map_create.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcelik <tcelik@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 13:31:33 by tcelik            #+#    #+#             */
/*   Updated: 2023/07/24 13:31:36 by tcelik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	fill_player_dir(t_cub3d *vals, double x, double y)
{
	vals->player.dir_x = x;
	vals->player.dir_y = y;
	if (x < 0.0)
		vals->player.plane_y = -0.66;
	else if (x > 0.0)
		vals->player.plane_y = 0.66;
	else
		vals->player.plane_y = 0;

	if (y < 0.0)
		vals->player.plane_x = 0.66;
	else if (y > 0.0)
		vals->player.plane_x = -0.66;
	else
		vals->player.plane_x = 0;
}

void	fill_int_val(t_cub3d *vals, int i, int j)
{
	if (ft_isdigit(vals->c_map[i][j]))
		vals->map[i][j] = vals->c_map[i][j] - 48;
	else
		vals->map[i][j] = 0;
	if (vals->c_map[i][j] == 'N')
		fill_player_dir(vals, 0.0, -1.0);
	else if (vals->c_map[i][j] == 'S')
		fill_player_dir(vals, 0.0, 1.0);
	else if (vals->c_map[i][j] == 'W')
		fill_player_dir(vals, -1.0, 0.0);
	else if (vals->c_map[i][j] == 'E')
		fill_player_dir(vals, 1.0, 0.0);
	if (is_user_char(vals->c_map[i][j]))
	{
		vals->player.x = (double) j + 0.5;
		vals->player.y = (double) i + 0.5;
	}
}

void	fill_int_map(t_cub3d *vals)
{
	int	i;
	int	j;

	i = -1;
	while (vals->c_map[++i])
	{
		j = -1;
		while (vals->c_map[i][++j])
		{
			fill_int_val(vals, i, j);
		}
	}
	double_free(vals->c_map);
}

void	allocate_int_map(t_cub3d *vals)
{
	int	i;

	vals->map_width = ft_strlen(vals->c_map[0]);
	vals->map_height = 0;
	while (vals->c_map[vals->map_height] != NULL)
		vals->map_height++;
	vals->map = (int **) malloc(sizeof(int *) * vals->map_height);
	if (!vals->map)
		free_exit(vals);
	i = -1;
	while (++i < vals->map_height)
	{
		vals->map[i] = (int *) malloc(sizeof(int) * vals->map_width);
		if (!vals->map[i])
			free_exit(vals);
	}
}

void	map_char_to_int(t_cub3d *vals)
{
	allocate_int_map(vals);
	fill_int_map(vals);
}
