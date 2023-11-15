/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkoletzk <lkoletzk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 17:05:46 by lkoletzk          #+#    #+#             */
/*   Updated: 2022/11/17 17:51:52 by lkoletzk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	size_t			i;
	unsigned char	*pstr;

	i = 0;
	pstr = (unsigned char *)str;
	while (i < n)
	{
		if (pstr[i] == (unsigned char)c)
			return (&pstr[i]);
		i++;
	}
	return (NULL);
}
