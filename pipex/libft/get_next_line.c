/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_livia.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkoletzk <lkoletzk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 13:55:24 by lkoletzk          #+#    #+#             */
/*   Updated: 2023/05/17 12:41:52 by lkoletzk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_join(char *s1, char *s2)
{
	char	*new_stock;

	if (!s1)
	{
		s1 = malloc(sizeof(char));
		if (!s1)
			return (NULL);
		s1[0] = '\0';
	}
	if (!s2)
		return (NULL);
	new_stock = ft_calloc((ft_strlen(s1) + ft_strlen(s2) + 1), sizeof(char));
	if (!new_stock)
		return (NULL);
	ft_strlcpy(new_stock, s1, ft_strlen(s1) + 1);
	ft_strlcat(new_stock, s2, ft_strlen(s1) + ft_strlen(s2) + 1);
	free(s1);
	return (new_stock);
}

/*----- Lis x catacteres (BUFFER_SIZE) dans le fichier (fd) -----*/
char	*readline(int fd, char *stockage)
{
	char	buffer[BUFFER_SIZE + 1];
	int		nbytes;

	buffer[0] = '\0';
	nbytes = 1;
	while (nbytes > 0 && !ft_strchr(stockage, '\n'))
	{
		nbytes = read(fd, buffer, BUFFER_SIZE);
		if (nbytes > 0)
		{
			buffer[nbytes] = '\0';
			stockage = ft_join(stockage, buffer);
		}
	}
	if (nbytes == -1)
		return (NULL);
	return (stockage);
}

/*----- Cree la ligne a renvoyer -----*/
char	*createline(char *stockage)
{
	char	*line;
	int		i;

	i = 0;
	if (!stockage[0])
		return (NULL);
	while (stockage[i] != '\n' && stockage[i] != '\0')
		i++;
	if (stockage[i] == '\n')
		i++;
	line = malloc((i + 1) * sizeof(char));
	if (!line)
		return (NULL);
	ft_strlcpy(line, stockage, i + 1);
	return (line);
}

/*----- Recupere le reste du stockage (apres le retour a la ligne) -----*/
char	*restline(char *stockage)
{
	char	*new_stock;
	int		i;

	i = 0;
	if (stockage[i] == '\0')
	{
		free(stockage);
		return (NULL);
	}
	while (stockage[i] != '\n' && stockage[i] != '\0')
		i++;
	if (stockage[i] == '\0')
		return (NULL);
	i++;
	new_stock = ft_calloc((ft_strlen(stockage) - i + 1), sizeof(char));
	if (!new_stock)
		return (NULL);
	ft_strlcpy(new_stock, stockage + i, ft_strlen(stockage) - i + 1);
	free(stockage);
	return (new_stock);
}

char	*get_next_line(int fd)
{
	static char	*stockage;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!stockage || (stockage && !ft_strchr(stockage, '\n')))
		stockage = readline(fd, stockage);
	if (!stockage)
		return (NULL);
	line = createline(stockage);
	stockage = restline(stockage);
	if (stockage && !stockage[0])
	{
		free(stockage);
		stockage = NULL;
	}
	return (line);
}

/*#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int	main(void)
{
	int	fd;
	char	*line;
	int	i;

	i = 1;
	fd = open("../Tristesse", O_RDONLY);

	printf("ligne %i : |%s|\n", i++, line = get_next_line(fd));
	free(line);
	printf("ligne %i : |%s|\n", i++, line = get_next_line(fd));
	free(line);
	printf("ligne %i : |%s|\n", i++, line = get_next_line(fd));
	free(line);
	printf("ligne %i : |%s|\n", i++, line = get_next_line(fd));
	free(line);
	printf("ligne %i : |%s|\n", i++, line = get_next_line(fd));
	free(line);
	printf("ligne %i : |%s|\n", i++, line = get_next_line(fd));
	free(line);
	printf("ligne %i : |%s|\n", i++, line = get_next_line(fd));
	free(line);
	printf("ligne %i : |%s|\n", i++, line = get_next_line(fd));
	free(line);
	printf("ligne %i : |%s|\n", i++, line = get_next_line(fd));
	free(line);
	printf("ligne %i : |%s|\n", i++, line = get_next_line(fd));
	free(line);
	printf("ligne %i : |%s|\n", i++, line = get_next_line(fd));
	free(line);
	printf("ligne %i : |%s|\n", i++, line = get_next_line(fd));
	free(line);
	printf("ligne %i : |%s|\n", i++, line = get_next_line(fd));
	free(line);
	printf("ligne %i : |%s|\n", i++, line = get_next_line(fd));
	free(line);
	printf("ligne %i : |%s|\n", i++, line = get_next_line(fd));
	free(line);
	printf("ligne %i : |%s|\n", i++, line = get_next_line(fd));
	free(line);
	printf("ligne %i : |%s|\n", i++, line = get_next_line(fd));
	free(line);
	printf("ligne %i : |%s|\n", i++, line = get_next_line(fd));
	free(line);
	printf("ligne %i : |%s|\n", i++, line = get_next_line(fd));
	free(line);
	printf("ligne %i : |%s|\n", i++, line = get_next_line(fd));
	free(line);



	close(fd);
}*/
