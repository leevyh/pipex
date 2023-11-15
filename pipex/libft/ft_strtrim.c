/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkoletzk <lkoletzk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 10:35:20 by lkoletzk          #+#    #+#             */
/*   Updated: 2022/11/22 10:35:20 by lkoletzk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_ischarset(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static size_t	ft_getlen(char const *s1, char const *set)
{
	size_t	i;
	size_t	len;

	len = ft_strlen(s1);
	i = 0;
	while (ft_ischarset(s1[len - i - 1], set) == 1)
		i++;
	return (len - i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	len;
	char	*s2;

	i = 0;
	len = 0;
	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup(s1));
	while (ft_ischarset(s1[i], set) == 1)
		i++;
	if (i == ft_strlen(s1))
		return (ft_strdup(""));
	len = ft_getlen(s1 + i, set);
	s2 = ft_calloc(len + 1, sizeof(char));
	if (!s2)
		return (NULL);
	ft_strlcpy(s2, s1 + i, len + 1);
	return (s2);
}

/*int main()
{
    char *result = ft_strtrim(" ;:gkjhg grg rrgr", " ;:");
    printf("%s\n", result);
    free(result);

    result = ft_strtrim(" ;:gkjhg grg rrgr:", " ;:");
    printf("%s\n", result);
    free(result);

    result = ft_strtrim("gkjhg grg rrgr", " ;:");
    printf("%s\n", result);
    free(result);

    result = ft_strtrim("", " :");
    printf("%s\n", result);
    free(result);

    result = ft_strtrim(" ;:gkjhg grg rrgr:", "");
    printf("%s\n", result);
    free(result);
    return 0;
}*/
