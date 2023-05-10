/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkoletzk <lkoletzk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:44:02 by lkoletzk          #+#    #+#             */
/*   Updated: 2022/12/12 15:27:29 by lkoletzk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	int		i;
	char	*p;

	i = 0;
	p = (char *)str;
	if (!str)
		return (0);
	while (p[i] != '\0')
	{
		if (p[i] == (unsigned char)c)
			return (&p[i]);
		i++;
	}
	if (p[i] == (unsigned char)c && (unsigned char)c == '\0')
		return (&p[i]);
	return (NULL);
}
