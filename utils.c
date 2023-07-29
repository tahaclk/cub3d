/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcelik <tcelik@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 13:46:21 by tcelik            #+#    #+#             */
/*   Updated: 2023/07/21 13:46:23 by tcelik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_map_char(int c)
{
	if (c == '1' || c == '0' || c == 'N' || c == 'S' || c == 'W' || c == 'E')
		return (1);
	return (0);
}

void	double_free(char **vals)
{
	int	i;

	i = 0;
	if (vals)
	{
		while (vals[i])
			free(vals[i++]);
		free(vals);
	}
}

int	closee(int keycode, t_cub3d *vals)
{
	int	i;
	int	j;

	i = -1;

	while (++i < vals->map_height)
		if (vals->map[i])
			free(vals->map[i]);
	if (vals->map)
		free(vals->map);
	free_tex_image2("Cub3d closed successfully!\n", vals, EXIT_SUCCESS);
	exit(EXIT_SUCCESS);
	return (0);
}

int	red_x_close(int keycode, t_cub3d *vals)
{
	printf("Cub3d closed successfully!\n");
	exit(EXIT_SUCCESS);
	return (0);
}

void	msg_fail_exit(char *msg, t_cub3d *vals, int exit_status)
{
	mlx_destroy_window(vals->mlx, vals->img.win);
	mlx_destroy_image(vals->mlx, vals->img.image);
	printf("%s", msg);
	exit(exit_status);
}
