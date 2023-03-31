/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkoletzk <lkoletzk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 15:10:34 by lkoletzk          #+#    #+#             */
/*   Updated: 2022/11/17 17:54:06 by lkoletzk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strcat(char *result, const char *s1, const char *s2, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i + j < len)
	{
		while (s1[i] != '\0')
		{
			result[i] = s1[i];
			i++;
		}
		while (s2[j] != '\0')
		{
			result[i + j] = s2[j];
			j++;
		}
	}
	return (result);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	char	*result;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	result = ft_calloc((len + 1), sizeof(char));
	if (!result)
		return (NULL);
	ft_strcat(result, s1, s2, len);
	return (result);
}

/*#include <stdio.h>

int	main(void)
{
	char	s1[] = "Je suis une patate";
	char	s2[] = " qui mange une patate.";

	char	*result;
	result = ft_strjoin(s1, s2);
	printf("%s\n", result);
	free(result);
}*/
