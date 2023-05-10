/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkoletzk <lkoletzk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 15:14:10 by lkoletzk          #+#    #+#             */
/*   Updated: 2022/11/18 16:33:48 by lkoletzk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_intsize(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len = 1;
	while (n != 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int				len;
	int				sign;
	unsigned int	nb;
	char			*result;

	len = ft_intsize(n);
	sign = 0;
	nb = n;
	if (n < 0)
	{
		sign = 1;
		nb = -n;
	}
	result = ft_calloc(len + 1, sizeof(char));
	if (!result)
		return (NULL);
	while (len--)
	{
		result[len] = nb % 10 + '0';
		nb = nb / 10;
	}
	if (sign == 1)
		result[0] = '-';
	return (result);
}
