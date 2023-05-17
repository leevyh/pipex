/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkoletzk <lkoletzk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 10:49:26 by lkoletzk          #+#    #+#             */
/*   Updated: 2023/05/17 14:05:30 by lkoletzk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// MADATORY VERSION
int	main(int argc, char **argv, char **envp)
{
	int		i;
	t_pipe	pipex;

	if (argc < 5)
	{
		write(2, "Error: Unvalid number of arguments\n", 36);
		exit(EXIT_FAILURE);
	}
	i = 2;
	if (ft_here_doc(argc, argv) > 0)
		i = 3;
	
	if(pipe(pipex.fd) == -1)
		ft_perror("Pipe");
	pipex.pid = fork();
	if (pipex.pid == -1)
		exit(EXIT_FAILURE);
	if (pipex.pid == 0)
		ft_1st_child_process(&pipex, argv, envp, i);
	pipex.pid = fork();
	if (pipex.pid == -1)
		exit(EXIT_FAILURE);
	if (pipex.pid == 0)
		ft_last_child_process(&pipex, argc, argv, envp);

	close(pipex.fd[0]);
	close(pipex.fd[1]);
	wait(NULL);
	return (0);
}

// BONUS VERSION
/*int	main(int argc, char **argv, char **envp)
{
	int		i;
	t_pipe	pipex;

	if (argc < 5)
	{
		write(2, "Error: Unvalid number of arguments\n", 36);
		exit(EXIT_FAILURE);
	}
	i = 2;
	if (ft_here_doc(argc, argv) > 0) // Check si le premier arg est "here_doc"
		i = 3;
	
	
	ft_1st_child_process(&pipex, argv, envp, i);
	while (++i < argc - 2)
		ft_mid_child_process(&pipex, argv, envp, i);
	ft_last_child_process(&pipex, argc, argv, envp);

	close(pipex.fd[0]);
	close(pipex.fd[1]);
	wait(NULL);
	// waitpid(pipex.pid1, NULL, 0);
	// waitpid(pipex.pid2, NULL, 0);
	return (0);
}*/
