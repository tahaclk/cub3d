/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcelik <tcelik@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 18:41:59 by tcelik            #+#    #+#             */
/*   Updated: 2023/07/21 18:42:01 by tcelik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_color_depth(t_cub3d *vals, t_color *color)
{
	if (color->r > 255 || color->r < 0)
		free_exit(vals);
	if (color->g > 255 || color->g < 0)
		free_exit(vals);
	if (color->b > 255 || color->b < 0)
		free_exit(vals);
}

int	fill_color(t_cub3d *vals, t_color *color, char *str)
{
	int		i;
	char	**clr;

	clr = ft_split(str, ',');
	i = 0;
	if (clr)
		while (clr[i])
			i++;
	if (i == 3)
	{
		color->r = ft_atoi(clr[0]);
		color->g = ft_atoi(clr[1]);
		color->b = ft_atoi(clr[2]);
		free(clr[0]);
		free(clr[1]);
		free(clr[2]);
		free(clr);
		check_color_depth(vals, color);
	}
	else
	{
		free_exit(vals);
		return (0);
	}
	return (1);
}

int	take_color(t_cub3d *vals, int i, char *key, t_color *color)
{
	char	*str;
	char	**clr;

	if (ft_strnstr(vals->c_map[i], key, 2) == vals->c_map[i])
	{
		str = ft_strnstr(vals->c_map[i], key, 2) + 1;
		while (*str >= 9 && *str <= 13 || *str == ' ')
			str++;
		if (ft_isdigit(*str))
			return (fill_color(vals, color, str));
	}
	return (0);
}

int	take_tx_path(t_cub3d *vals, int i, char *key, char **path)
{
	char	*str;

	if (ft_strnstr(vals->c_map[i], key, 4) == vals->c_map[i])
	{
		str = ft_strnstr(vals->c_map[i], key, 4) + 2;
		while (*str >= 9 && *str <= 13 || *str == ' ')
			str++;
		if (ft_isprint(*str))
		{
			*path = ft_strdup(str);
			return (1);
		}
	}
	return (0);
}

int	take_data(t_cub3d *vals, int i)
{
	if (take_tx_path(vals, i, "NO ", &(vals->north.path)) == 1)
		return (1);
	else if (take_tx_path(vals, i, "SO ", &(vals->south.path)) == 1)
		return (1);
	else if (take_tx_path(vals, i, "EA ", &(vals->east.path)) == 1)
		return (1);
	else if (take_tx_path(vals, i, "WE ", &(vals->west.path)) == 1)
		return (1);
	else if (take_color(vals, i, "F ", &(vals->floor)) == 1)
		return (1);
	else if (take_color(vals, i, "C ", &(vals->sky)) == 1)
		return (1);
	else if (vals->c_map[i])
	{
		if (vals->c_map[i][0] == '\n')
			;
		else
			free_exit(vals);
	}
	else
		free_exit(vals);
	return (0);
}
