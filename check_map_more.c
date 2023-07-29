/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_more.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcelik <tcelik@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 18:51:25 by tcelik            #+#    #+#             */
/*   Updated: 2023/07/29 18:51:26 by tcelik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_after_newl(t_cub3d *vals, char *str, int i, int fd)
{
	while (str[i])
	{
		if (str[i] == '\n')
			i++;
		else
		{
			close(fd);
			free_tex_image("ERROR\nMap is splited with new line!\n", vals);
		}
	}
	return (i);
}

int	check_6_after(t_cub3d *vals, char *str, int i, int fd)
{
	while (str[i])
	{
		if (str[i] == '\n')
			i++;
		else
		{
			while (str[i])
			{
				if (str[i] != '\n')
					i++;
				else
				{
					if (str[i + 1] == '\n')
						i = check_after_newl(vals, str, i, fd);
					else
						i++;
				}
			}
		}
	}
	return (i);
}

void	check_6(t_cub3d *vals, char *str, int fd)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			i++;
		else if (str[i] != '\n')
		{
			count++;
			while (str[i])
			{
				if (str[i] != '\n')
					i++;
				else
					break ;
			}
		}
		if (count == 6)
			i = check_6_after(vals, str, i, fd);
	}
}

void	check_split_map(t_cub3d *vals, char **av)
{
	char	*str;
	char	*tmp;
	int		fd;

	fd = open_file(vals, av);
	str = get_next_line(fd);
	if (!str)
	{
		close(fd);
		free_tex_image("File is empty or file cannot be opened\n", vals);
	}
	while (1)
	{
		tmp = get_next_line(fd);
		if (!tmp)
			break ;
		str = ft_strjoin2(str, tmp);
		free(tmp);
	}
	check_6(vals, str, fd);
}
