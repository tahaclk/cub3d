/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcelik <tcelik@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 17:55:02 by tcelik            #+#    #+#             */
/*   Updated: 2023/07/29 17:55:03 by tcelik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_color_depth(t_cub3d *vals, t_color *color)
{
	if (color->r > 255 || color->r < 0)
		free_tex_paths("ERROR\nColor value depth is wrong!\n",
			vals, EXIT_FAILURE);
	if (color->g > 255 || color->g < 0)
		free_tex_paths("ERROR\nColor value depth is wrong!\n",
			vals, EXIT_FAILURE);
	if (color->b > 255 || color->b < 0)
		free_tex_paths("ERROR\nColor value depth is wrong!\n",
			vals, EXIT_FAILURE);
}

int	is_all_digit(char **clr)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (clr[i])
	{
		j = 0;
		while (clr[i][j])
		{
			if (ft_isdigit(clr[i][j]))
				j++;
			else
				return (0);
		}
		i++;
	}
	return (1);
}
