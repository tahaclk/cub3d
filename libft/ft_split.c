/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcelik <tcelik@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 12:17:59 by tcelik            #+#    #+#             */
/*   Updated: 2022/10/12 15:28:04 by tcelik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	word_counter(char const *s, char c)
{
	size_t	i;
	int		words;
	int		important;

	i = 0;
	words = 0;
	important = 0;
	while (s[i])
	{
		if (s[i] != c && important == 0)
		{
			important = 1;
			words++;
		}
		else if (s[i] == c)
			important = 0;
		i++;
	}
	return (words);
}

char	*word_create(char	*s, char c)
{
	char	*str;
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	str = (char *)malloc(i + 1);
	i = 0;
	while (s[i] && s[i] != c)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	size_t	i;
	size_t	j;

	if (!s)
		return (NULL);
	i = word_counter (s, c);
	j = 0;
	split = (char **)malloc((i + 1) * sizeof(char *));
	if (!split)
		return (NULL);
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else if (s[i] != c)
		{
			split[j++] = word_create((char *)&s[i], c);
			while (s[i] != c && s[i])
				i++;
		}
	}
	split[j] = 0;
	return (split);
}
