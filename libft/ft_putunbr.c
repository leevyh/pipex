/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunbr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkoletzk <lkoletzk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 12:34:43 by lkoletzk          #+#    #+#             */
/*   Updated: 2022/12/12 14:36:18 by lkoletzk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_uintlen(unsigned int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		return (1);
	while (n != 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

static char	*ft_utoa(unsigned int n)
{
	int				len;
	unsigned int	nb;
	char			*result;

	len = ft_uintlen(n);
	nb = n;
	result = ft_calloc(len + 1, sizeof(char));
	if (!result)
		return (NULL);
	while (len--)
	{
		result[len] = nb % 10 + '0';
		nb = nb / 10;
	}
	return (result);
}

/*----- format = %u -----*/
int	ft_putunbr(unsigned int nb)
{
	char	*str;
	int		len;

	str = ft_utoa(nb);
	len = ft_strlen(str);
	write (1, str, len);
	free(str);
	return (len);
}
