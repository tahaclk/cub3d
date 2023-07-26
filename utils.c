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

void	free_exit(t_cub3d *vals)
{
	/*if (vals->north.path)
		free(vals->north.path);
	if (vals->south.path)
		free(vals->south.path);
	if (vals->east.path)
		free(vals->east.path);
	if (vals->west.path)
		free(vals->west.path);
	while (*(vals->map))
		free(*(vals->map)++);
	free(vals->map);*/
	msg_fail_exit("DATA BROKE\nERROR\n");
}

int	closee(int keycode, t_cub3d *vars)
{
	system("leaks cub3d");
	exit(EXIT_SUCCESS);
	return (0);
}

void	msg_fail_exit(char *msg)
{
	printf("%s", msg);
	system("leaks cub3d");
	exit(EXIT_FAILURE);
}
