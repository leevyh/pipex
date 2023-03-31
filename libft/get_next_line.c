/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkoletzk <lkoletzk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 13:55:24 by lkoletzk          #+#    #+#             */
/*   Updated: 2022/12/12 15:28:38 by lkoletzk         ###   ########.fr       */
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
	new_stock = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!new_stock)
		return (NULL);
	ft_strlcpy(new_stock, s1, ft_strlen(s1) + 1);
	ft_strlcat(new_stock, s2, ft_strlen(s1) + ft_strlen(s2) + 1);
	free(s1);
	return (new_stock);
}

/*----- Lis x catacteres (BUFFER_SIZE) dans le fichier (fd) -----*/
static char	*readline(int fd, char *stockage)
{
	char	*buffer;
	int		nbytes;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
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
	free(buffer);
	if (nbytes == -1)
		return (NULL);
	return (stockage);
}

/*----- Cree la ligne a renvoyer -----*/
static char	*createline(char *stockage)
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
static char	*restline(char *stockage)
{
	char	*new_stock;
	int		i;

	i = 0;
	while (stockage[i] != '\n' && stockage[i] != '\0')
		i++;
	if (stockage[i] == '\0')
		return (NULL);
	i++;
	new_stock = malloc((ft_strlen(stockage) - i + 1) * sizeof(char));
	if (!new_stock)
		return (NULL);
	ft_strlcpy(new_stock, stockage + i, ft_strlen(stockage) - i + 1);
	return (new_stock);
}

char	*get_next_line(int fd)
{
	static char	*stockage[1024];
	char		*line;
	char		*tmp;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!stockage[fd] || (stockage[fd] && !ft_strchr(stockage[fd], '\n')))
		stockage[fd] = readline(fd, stockage[fd]);
	if (!stockage[fd])
		return (NULL);
	line = createline(stockage[fd]);
	tmp = restline(stockage[fd]);
	free(stockage[fd]);
	stockage[fd] = tmp;
	return (line);
}

/*#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int	main(void)
{
	int	fd1;
	int	fd2;
	int	fd3;
	char	*line;
	int	i;

	i = 1;
	fd1 = open("Tristesse", O_RDONLY);
	fd2 = open("Blague", O_RDONLY);
	fd3 = open("Confiture de nouilles", O_RDONLY);

	printf("ligne %i : |%s|\n", i++, line = get_next_line(fd1));
	free(line);
	printf("ligne %i : |%s|\n", i++, line = get_next_line(fd2));
	free(line);
	printf("ligne %i : |%s|\n", i++, line = get_next_line(fd3));
	free(line);
	printf("ligne %i : |%s|\n", i++, line = get_next_line(fd1));
	free(line);
	printf("ligne %i : |%s|\n", i++, line = get_next_line(fd2));
	free(line);
	printf("ligne %i : |%s|\n", i++, line = get_next_line(fd3));
	free(line);
	printf("ligne %i : |%s|\n", i++, line = get_next_line(fd1));
	free(line);
	printf("ligne %i : |%s|\n", i++, line = get_next_line(fd2));
	free(line);
	printf("ligne %i : |%s|\n", i++, line = get_next_line(fd3));
	free(line);
	printf("ligne %i : |%s|\n", i++, line = get_next_line(fd1));
	free(line);
	printf("ligne %i : |%s|\n", i++, line = get_next_line(fd2));
	free(line);
	printf("ligne %i : |%s|\n", i++, line = get_next_line(fd3));
	free(line);
	printf("ligne %i : |%s|\n", i++, line = get_next_line(fd1));
	free(line);
	printf("ligne %i : |%s|\n", i++, line = get_next_line(fd2));
	free(line);
	printf("ligne %i : |%s|\n", i++, line = get_next_line(fd3));
	free(line);
	printf("ligne %i : |%s|\n", i++, line = get_next_line(fd1));
	free(line);
	printf("ligne %i : |%s|\n", i++, line = get_next_line(fd2));
	free(line);
	printf("ligne %i : |%s|\n", i++, line = get_next_line(fd3));
	free(line);

	close(fd1);
	close(fd2);
	close(fd3);
}*/
