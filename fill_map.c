/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcelik <tcelik@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 14:16:10 by tcelik            #+#    #+#             */
/*   Updated: 2023/07/22 14:16:13 by tcelik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	find_line_count(t_cub3d *vals, int i)
{
	int	line_count;

	line_count = 0;
	while (vals->c_map[i])
	{
		line_count++;
		i++;
	}
	return (line_count);
}

int	find_longest_line(t_cub3d *vals, int i)
{
	int	max_size;

	max_size = -1;
	while (vals->c_map[++i])
	{
		if (ft_strlen(vals->c_map[i]) > max_size)
			max_size = ft_strlen(vals->c_map[i]);
	}
	return (max_size);
}

void	fill_map(t_cub3d *vals, char **map, int map_start_idx, int max_line)
{
	int	j;
	int	idx;
	int	line_count;

	idx = map_start_idx - 1;
	j = -1;
	line_count = find_line_count(vals, map_start_idx);
	while (++idx < line_count + map_start_idx)
	{
		j = -1;
		while (vals->c_map[idx][++j])
		{
			if (vals->c_map[idx][j] == ' ')
				map[idx - map_start_idx][j] = '1';
			else
				map[idx - map_start_idx][j] = vals->c_map[idx][j];
		}
		while (j < max_line)
			map[idx - map_start_idx][j++] = '1';
		map[idx - map_start_idx][j] = '\0';
	}
	check_map(vals, map_start_idx, map);
	double_free(vals->c_map);
	vals->c_map = map;
	check_map_chars(vals);
}

char	**double_malloc(t_cub3d *vals, int line_count, int max_line_size)
{
	char	**map;
	int		j;

	j = -1;
	map = (char **) malloc(sizeof(char *) * (line_count + 1));
	if (!map)
		free_exit(vals);
	while (++j < line_count)
	{
		map[j] = (char *) malloc(sizeof(char) * (max_line_size + 1));
		if (!map[j])
		{
			while (--j >= 0)
				free(map[j]);
			free(map);
		}
	}
	map[j] = 0;
	return (map);
}

void	init_map_data(t_cub3d *vals, int *map_start_index)
{
	int		j;
	int		line_count;
	int		max_line_size;
	char	**map;

	j = -1;
	if (*map_start_index == -1)
		msg_fail_exit("Map not found pls check map!\nERROR\n");
	else
	{
		line_count = find_line_count(vals, *map_start_index);
		if (line_count != 0)
		{
			max_line_size = find_longest_line(vals, *map_start_index);
			if (max_line_size == 0)
				free_exit(vals);
		}
		else
			free_exit(vals);
		map = double_malloc(vals, line_count, max_line_size);
		fill_map(vals, map, *map_start_index, max_line_size);
	}
}
