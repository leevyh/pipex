/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkoletzk <lkoletzk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 10:49:26 by lkoletzk          #+#    #+#             */
/*   Updated: 2023/05/10 17:51:23 by lkoletzk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* Il faut pipe les fd avant de fork pour que les enfants puissent en heriter
1- On check les fds pour verifier l'existance de*/
int	main(int argc, char **argv, char **envp)
{
	t_pipe	pipex;
	int		here_doc;

	here_doc = 0;
	if (argc > 1 && !ft_strncmp(argv[1], "here_doc", 8))
		here_doc++;
	if (argc < 5)
	{
		write(2, "Unvalid number of arguments\n", 28);
		exit(EXIT_FAILURE);
	}
	if (here_doc == 1)
		ft_pipex_heredoc();
	else
		ft_pipex_bonus();
	return (EXIT_SUCCESS);
	pipex.paths = ft_find_command_paths(envp);
	// if (!pipex.paths)
	// 	return (1);
	if(pipe(pipex.fd) == -1)
		ft_perror("Pipe", pipex);
	pipex.pid1 = fork();
	if (pipex.pid1 == 0)							// Mettre protection
		ft_1st_child_process(pipex, argv, envp);
	pipex.pid2 = fork();
	if (pipex.pid2 == 0)							// Mettre protection
		ft_2nd_child_process(pipex, argv, envp);
	close(pipex.fd[0]);
	close(pipex.fd[1]);
	ft_free_all(pipex);
	waitpid(pipex.pid1, NULL, 0);
	waitpid(pipex.pid2, NULL, 0);
	return (0);
}
