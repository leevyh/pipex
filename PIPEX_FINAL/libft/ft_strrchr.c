/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkoletzk <lkoletzk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 15:47:28 by lkoletzk          #+#    #+#             */
/*   Updated: 2022/11/22 17:13:03 by lkoletzk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int		i;
	int		j;
	char	*p;

	i = 0;
	j = -1;
	p = (char *)str;
	while (p[i] != '\0')
	{
		if (p[i] == (unsigned char)c)
			j = i;
		i++;
	}
	if (p[i] == (unsigned char)c && (unsigned char)c == '\0')
		return (&p[i]);
	if (j < 0)
		return (0);
	return (&p[j]);
}
