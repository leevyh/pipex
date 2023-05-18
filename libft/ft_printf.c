/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkoletzk <lkoletzk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 15:10:33 by lkoletzk          #+#    #+#             */
/*   Updated: 2022/12/12 15:13:09 by lkoletzk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_conversions(const char *str, int i, va_list conv);

int	ft_printf(const char *str, ...)
{
	va_list	conv;
	int		i;
	int		result;

	i = 0;
	result = 0;
	if (!str)
		return (-1);
	va_start(conv, str);
	while (str[i] != '\0')
	{
		if (str[i] == '%' && ft_strchr("cspdiuxX%", str[i + 1]))
		{
			if (str[i + 1] == '\0')
				return (-1);
			result = result + ft_conversions(str, i, conv);
			i++;
		}
		else
			result = result + ft_putchar(str[i]);
		i++;
	}
	va_end(conv);
	return (result);
}

int	ft_conversions(const char *str, int i, va_list conv)
{
	if (str[i + 1] == '%')
		return (ft_putchar(str[i + 1]));
	if (str[i + 1] == 'c')
		return (ft_putchar(va_arg(conv, int)));
	if (str[i + 1] == 's')
		return (ft_putstr(va_arg(conv, char *)));
	if (str[i + 1] == 'p')
		return (ft_putptr(va_arg(conv, void *), "0123456789abcdef"));
	if (str[i + 1] == 'd' || str[i + 1] == 'i')
		return (ft_putnbr(va_arg(conv, int)));
	if (str[i + 1] == 'u')
		return (ft_putunbr(va_arg(conv, unsigned int)));
	if (str[i + 1] == 'x')
		return (ft_putx(va_arg(conv, unsigned int), "0123456789abcdef"));
	if (str[i + 1] == 'X')
		return (ft_putx(va_arg(conv, unsigned int), "0123456789ABCDEF"));
	return (0);
}

/*#include <limits.h>
#include <stdio.h>
int	main()
{
//	int	n = ft_printf("%%%c%%%s%%%d%%%i%%%u%%%x%%%X%%%% %c%%", 'c', "0", 
//		0, 0 ,0 ,0, 42, 0);
//	ft_printf("result : %d\n", n);
//	n = printf("%%%c%%%s%%%d%%%i%%%u%%%x%%%X%%%% %c%%", 'c', "0", 
//		0, 0 ,0 ,0, 42, 0);
//	printf("result : %d\n", n);

//	unsigned int	nb = ft_printf("Nous sommes %x patates\n", 42);
//	ft_printf("result : %d\n", nb);
//	nb = printf("Nous sommes %x patates\n", 42);
//	printf("result : %d\n", nb);

//	void *ptr = NULL;
//	unsigned int	nb = ft_printf("%p\n", ptr);
//	ft_printf("result : %d\n", nb);
//	nb = printf("%p\n", ptr);
//	printf("result : %d\n", nb);

//	char str[] = "Je suis une patate";
//	nb = ft_printf("%p\n", str);
//	ft_printf("result : %d\n", nb);
//	nb = printf("%p\n", str);
//	printf("result : %d\n", nb);

//	int	nb = ft_printf("%u\n", -4200000);
//	ft_printf("result : %d\n", nb);
//	nb = printf("%u\n", -4200000);
//	printf("result : %d\n", nb);

//	int	test = ft_printf("%d\n", 0);
//	ft_printf("result : %d\n", test);
//	test = printf("%d\n", 0);
//	printf("result : %d\n", test);
}*/
