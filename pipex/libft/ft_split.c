/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkoletzk <lkoletzk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 10:37:06 by lkoletzk          #+#    #+#             */
/*   Updated: 2022/11/22 10:37:06 by lkoletzk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_freetab(char **tab)
{
	int	x;

	x = 0;
	while (tab[x])
	{
		free(tab[x]);
		x++;
	}
	free(tab);
	return (NULL);
}

static size_t	ft_wordcount(const char *s, char c)
{
	size_t	i;
	size_t	words;

	i = 0;
	words = 0;
	if (s[0] == '\0')
		return (0);
	while (s[i] != '\0' && s[i] == c)
		i++;
	while (s[i] != '\0')
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			words++;
		i++;
	}
	return (words);
}

static void	ft_wordlen(char **cursor, size_t *len, char c)
{
	size_t	i;

	*cursor = *cursor + *len;
	*len = 0;
	i = 0;
	while (**cursor && **cursor == c)
		(*cursor)++;
	while ((*cursor)[i])
	{
		if ((*cursor)[i] == c)
			return ;
		(*len)++;
		i++;
	}
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	char	*cursor;
	size_t	len;
	size_t	x;

	if (!s)
		return (NULL);
	tab = ft_calloc(ft_wordcount(s, c) + 1, sizeof(char *));
	if (!tab)
		return (NULL);
	x = 0;
	cursor = (char *)s;
	len = 0;
	while (x < ft_wordcount(s, c))
	{
		ft_wordlen(&cursor, &len, c);
		tab[x] = ft_calloc(len + 1, sizeof(char));
		if (!tab[x])
			return (ft_freetab(tab));
		ft_strlcpy(tab[x], cursor, len + 1);
		x++;
	}
	return (tab);
}
