/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkoletzk <lkoletzk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 10:49:26 by lkoletzk          #+#    #+#             */
/*   Updated: 2023/05/11 18:23:38 by lkoletzk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipe	pipex;

	if (argc < 5)
	{
		write(2, "Unvalid number of arguments\n", 28);
		exit(EXIT_FAILURE);
	}
	if (argc >= 5)
        ft_here_doc(argv);

	if(pipe(pipex.fd) == -1)
		ft_perror("Pipe");
	pipex.pid1 = fork();
	if (pipex.pid1 == -1)
		exit(EXIT_FAILURE);
	if (pipex.pid1 == 0)
		ft_1st_child_process(pipex, argv, envp);
	pipex.pid2 = fork();
	if (pipex.pid2 == -1)
		exit(EXIT_FAILURE);
	if (pipex.pid2 == 0)
		ft_last_child_process(pipex, argc, argv, envp);

	close(pipex.fd[0]);
	close(pipex.fd[1]);
	waitpid(pipex.pid1, NULL, 0);
	waitpid(pipex.pid2, NULL, 0);
	return (0);
}
