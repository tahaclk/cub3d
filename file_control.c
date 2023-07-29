/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_control.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcelik <tcelik@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 15:09:30 by tcelik            #+#    #+#             */
/*   Updated: 2023/07/21 15:09:33 by tcelik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**read_file(t_cub3d *vals, int fd)
{
	char	**rtn;
	char	*str;
	char	*tmp;

	str = get_next_line(fd);
	if (!str)
	{
		close(fd);
		msg_fail_exit("File is empty or file cannot be opened\n", vals);
	}
	while (1)
	{
		tmp = get_next_line(fd);
		if (!tmp)
			break ;
		str = ft_strjoin2(str, tmp);
		free(tmp);
	}
	rtn = ft_split(str, '\n');
	if (str)
		free(str);
	return (rtn);
}

int	open_file(t_cub3d *vals, char **av)
{
	int		len;
	char	*str;

	len = ft_strlen(av[1]);
	if (len > 3)
	{
		if (av[1][len - 1] == 'b' && av[1][len - 2] == 'u' &&
			av[1][len - 3] == 'c' && av[1][len - 4] == '.')
		{
			str = ft_strjoin("./maps/", av[1]);
			len = open(str, O_RDONLY);
			if (str)
				free(str);
			if (len == -1)
				msg_fail_exit("File couldn't be opened\n", vals);
			return (len);
		}
		else
			msg_fail_exit("Wrong map name\n", vals);
	}
	else
		msg_fail_exit("Wrong map name\n", vals);
	return (0);
}
