/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkoletzk <lkoletzk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 12:27:17 by lkoletzk          #+#    #+#             */
/*   Updated: 2023/06/02 13:48:37 by lkoletzk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	ft_perror(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

char	**ft_freetab(char **tab)
{
	int	x;

	x = 0;
	while (tab[x])
	{
		free(tab[x]);
		x++;
	}
	free(tab);
	return (NULL);
}

void	ft_close_fds(int fd[])
{
	close(fd[0]);
	close(fd[1]);
}

void	ft_child_error(char **cmd_args, char **paths)
{
	ft_putstr_fd("command not found: ", 2);
	ft_putendl_fd(cmd_args[0], 2);
	if (paths)
		ft_freetab(paths);
	if (cmd_args)
		ft_freetab(cmd_args);
	exit(EXIT_FAILURE);
}
