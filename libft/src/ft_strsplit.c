/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharris <sharris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/12 13:35:33 by sharris           #+#    #+#             */
/*   Updated: 2018/07/12 13:35:33 by sharris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static int	get_split_count(char const *s, char c)
{
	int x;

	x = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s && *s != c)
		{
			x++;
			s++;
		}
		while (*s && *s != c)
			s++;
	}
	return (x);
}

static int	get_word_lc(char const *s, char c)
{
	int i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

char		**ft_strsplit(char const *s, char c)
{
	char	*word;
	char	**split;
	int		i;
	int		sc;

	sc = 0;
	if (!s || NULL == (split = (char **)ft_memalloc(sizeof(char *)
		* (get_split_count(s, c) + 1))))
		return (NULL);
	while (*s)
	{
		i = 0;
		while (*s && *s == c)
			s++;
		if (*s && *s != c)
		{
			word = ft_strnew(get_word_lc(s, c));
			while (*s && *s != c)
				word[i++] = *s++;
			split[sc++] = word;
		}
	}
	split[sc] = 0;
	return (split);
}
