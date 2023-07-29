/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcelik <tcelik@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 17:58:15 by tcelik            #+#    #+#             */
/*   Updated: 2023/07/22 17:58:17 by tcelik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_map(t_cub3d *vals, char **map, char *msg)
{
	double_free(map);
	free_tex_image(msg, vals);
}

int	check_player(t_cub3d *vals, char **map, int i, int j)
{
	static int	player_count;

	if (vals->c_map[i][j] == 'N' || vals->c_map[i][j] == 'S' ||
		vals->c_map[i][j] == 'W' || vals->c_map[i][j] == 'E')
		player_count++;
	return ((int) player_count);
}

void	check_map(t_cub3d *vals, int start_idx, char **map)
{
	int	i;
	int	j;
	int	player_count;

	i = start_idx - 1;
	while (vals->c_map[++i])
	{
		j = -1;
		while (vals->c_map[i][++j])
		{
			if (is_user_zero(vals->c_map[i][j]) && (j == 0 || i == start_idx ||
				vals->c_map[i][j + 1] == '\0' || vals->c_map[i + 1] == NULL))
				free_map(vals, map, "ERROR\nMap is not close with walls!\n");
			else if (is_user_zero(vals->c_map[i][j]) &&
				(vals->c_map[i][j - 1] == ' ' || vals->c_map[i][j + 1] == ' ' ||
				vals->c_map[i - 1][j] == ' ' || vals->c_map[i + 1][j] == ' '))
				free_map(vals, map, "ERROR\nMap is not close with walls!\n");
			else if (is_user_zero(vals->c_map[i][j]) && (ft_strlen(vals->c_map[i
				- 1]) - 1 < j || ft_strlen(vals->c_map[i + 1]) - 1 < j))
				free_map(vals, map, "ERROR\nMap is not close with CRASHS!\n");
			player_count = check_player(vals, map, i, j);
		}
	}
	if (player_count > 1 || player_count < 1)
		free_map(vals, map, "ERROR\nPlayers count not 1 on the map!\n");
}

void	check_map_chars(t_cub3d *vals)
{
	int	i;
	int	j;

	i = -1;
	while (vals->c_map[++i])
	{
		j = -1;
		while (vals->c_map[i][++j])
		{
			if (!is_map_char(vals->c_map[i][j]))
			{
				double_free(vals->c_map);
				free_tex_image2("ERROR\nIncorrect character on the map!\n", vals, EXIT_FAILURE);
			}
		}
	}
}
