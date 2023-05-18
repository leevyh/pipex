/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putxptr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkoletzk <lkoletzk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 11:07:25 by lkoletzk          #+#    #+#             */
/*   Updated: 2022/12/12 14:36:21 by lkoletzk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_uintlen(unsigned long nb)
{
	int	len;

	len = 0;
	if (nb == 0)
		return (1);
	while (nb > 0)
	{
		nb = nb / 16;
		len++;
	}
	return (len);
}

static char	*ft_utox(unsigned long nb, char *base)
{
	int		len;
	char	*str;

	len = ft_uintlen(nb);
	str = (char *)ft_calloc(len + 1, sizeof(char));
	if (!str)
		return (NULL);
	while (len > 0)
	{
		str[len - 1] = base[nb % 16];
		nb = nb / 16;
		len--;
	}
	return (str);
}

/*----- format = %x / %X -----*/
int	ft_putx(unsigned long nb, char *base)
{
	char	*str;
	int		len;

	str = ft_utox(nb, base);
	len = ft_putstr(str);
	free (str);
	return (len);
}

/*----- format = %p -----*/
int	ft_putptr(void *nb, char *base)
{
	char			*str;
	int				len;
	unsigned long	n;

	if (nb == NULL)
	{
		write (1, "(nil)", 5);
		return (5);
	}
	n = (unsigned long)nb;
	str = ft_utox(n, base);
	len = ft_strlen(str);
	ft_putstr("0x");
	write (1, str, len);
	free(str);
	return (2 + len);
}
