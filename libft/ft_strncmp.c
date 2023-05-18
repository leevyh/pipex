/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkoletzk <lkoletzk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:42:08 by lkoletzk          #+#    #+#             */
/*   Updated: 2023/05/12 13:41:05 by lkoletzk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*ps1;
	unsigned char	*ps2;

	i = 0;
	ps1 = (unsigned char *)s1;
	ps2 = (unsigned char *)s2;
	if (n == 0)
		return (0);
	while (ps1[i] != '\0' && ps2[i] != '\0' && i < n - 1)
	{
		if (ps1[i] != ps2[i])
			return (ps1[i] - ps2[i]);
		i++;
	}
	return (ps1[i] - ps2[i]);
}

// int	main(int argc, char **argv)
// {
// 	(void)argc;
// 	ft_printf("len: %d\n", ft_strlen(argv[1]));
// 	ft_printf("%d\n", ft_strncmp(argv[1], argv[2], ft_strlen(argv[1]) + 1));
// 	return (0);
// }
