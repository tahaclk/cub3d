/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcelik <tcelik@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 16:32:53 by tcelik            #+#    #+#             */
/*   Updated: 2023/07/22 16:32:55 by tcelik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_user_zero(int c)
{
	if (c == '0' || c == 'N' || c == 'S' || c == 'W' || c == 'E')
		return (1);
	return (0);
}

int	is_user_char(int c)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
		return (1);
	return (0);
}

void	put_pixel_in_img(t_cub3d *f, int x, int y, int color)
{
	char	*dst;

	dst = f->img.data + (y * f->img.sizeline + x * (f->img.bpp / 8));
	*(unsigned int *)dst = color;
}

unsigned int	get_pixel_in_tex(t_texture tex, int x, int y)
{
	char	*dst;

	dst = tex.data + (y * tex.sizeline + x * (tex.bpp / 8));
	return (*((unsigned int *) dst));
}

int	create_trgb(int t, int r, int g, int b)
{
	int x = 0x213;
	return (t << 24 | r << 16 | g << 8 | b);
}
