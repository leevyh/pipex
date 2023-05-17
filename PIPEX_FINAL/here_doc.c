/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkoletzk <lkoletzk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 17:42:37 by lkoletzk          #+#    #+#             */
/*   Updated: 2023/05/17 14:14:30 by lkoletzk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "pipex.h"

int	ft_here_doc(int argc, char **argv)
{
	int		fd;
	char	*line;

	if (!ft_strncmp("here_doc", argv[1], 9) && argc > 5)
	{
		write(1, "pipe here_doc> ", 15);
		line = get_next_line(0);
		fd = open("here_doc", O_RDWR | O_CREAT | O_TRUNC, 0777);
		while (line)
		{
			if (!ft_strncmp(argv[2], line, ft_strlen(argv[2]))
				&& line[ft_strlen(argv[2])] == '\n')
				break;
			write(1, "pipe here_doc> ", 15);
			ft_putstr_fd(line, fd);
			free(line);
			line = get_next_line(0);
		}
		free(line);
		close(fd);
		return (1);
	}
	return (0);
}
