/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkoletzk <lkoletzk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 17:48:20 by lkoletzk          #+#    #+#             */
/*   Updated: 2022/11/22 11:47:27 by lkoletzk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	int		len;
	char	*tab;
	int		i;

	len = ft_strlen(src);
	i = 0;
	if (!src)
		return (NULL);
	tab = (char *)ft_calloc(len + 1, sizeof(char));
	if (!tab)
		return (NULL);
	while (i < len)
	{
		tab[i] = src[i];
		i++;
	}
	return (tab);
}
