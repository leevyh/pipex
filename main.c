/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkoletzk <lkoletzk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 10:49:26 by lkoletzk          #+#    #+#             */
/*   Updated: 2023/04/13 17:08:58 by lkoletzk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* Il faut pipe les fd avant de fork pour que les enfants puissent en heriter*/
int	main(int argc, char **argv, char **envp)
{
	t_pipe	pipex;
	
	if (argc != 5)
		return (message("Unvalid number of arguments\n"));
	pipex.in = open(argv[1], O_RDONLY);
	pipex.out = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (pipex.in < 0 || pipex.out < 0)
	{
		perror("fd");
		exit (EXIT_FAILURE);
	}
	if(pipe(pipex.p_fd) == -1)
	{
		perror("Pipe");
		exit (EXIT_FAILURE);
	}
	pipex.paths = ft_find_command_paths(envp);
	pipex.pid1 = fork();
	if (pipex.pid1 == 0)
		ft_1st_child_process(pipex, argv, envp);
	pipex.pid2 = fork();
	if (pipex.pid2 == 0)
		ft_2nd_child_process(pipex, argv, envp);
	close(pipex.p_fd[0]);
	close(pipex.p_fd[1]);
	waitpid(pipex.pid1, NULL, 0);
	waitpid(pipex.pid2, NULL, 0);
	cmd_paths_free(&pipex);
}
