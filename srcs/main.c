/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkoletzk <lkoletzk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 10:49:26 by lkoletzk          #+#    #+#             */
/*   Updated: 2023/05/18 12:10:39 by lkoletzk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int			i;
	t_pipe_m	pipex;

	if (argc != 5)
	{
		write(2, "Error: Unvalid number of arguments\n", 36);
		exit(EXIT_FAILURE);
	}
	i = 2;
	if (pipe(pipex.fd) == -1)
		ft_perror("Pipe");
	ft_1st_child_process(&pipex, argv, envp);
	ft_lst_child_process(&pipex, argc, argv, envp);
	ft_close_fds(pipex.fd);
	while (wait(NULL) > 0)
		;
	return (0);
}
