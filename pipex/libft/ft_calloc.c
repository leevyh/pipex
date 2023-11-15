/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkoletzk <lkoletzk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 13:05:22 by lkoletzk          #+#    #+#             */
/*   Updated: 2022/11/17 17:50:54 by lkoletzk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t elementCount, size_t elementSize)
{
	void	*tab;
	int		testoverflow;

	testoverflow = (int)(elementCount * elementSize);
	if (elementSize != 0 && elementCount != (size_t)testoverflow / elementSize)
		return (NULL);
	tab = malloc(elementCount * elementSize);
	if (!tab)
		return (0);
	ft_bzero(tab, elementCount * elementSize);
	return (tab);
}
