/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkoletzk <lkoletzk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 10:49:26 by lkoletzk          #+#    #+#             */
/*   Updated: 2023/03/31 12:48:33 by lkoletzk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"



int	main(int argc, char **argv, char **envp)
{
	t_pipe	pipex;
	
	if (argc != 5)
		return (strerror("Unvalid number of arguments\n"));
	pipex.fd[0] = open(argv[1], O_RDONLY);
	pipex.fd[1] = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (pipex.fd[0] < 0 || pipex.fd[1] < 0)
	{
		perror("fd");
		exit (EXIT_FAILURE);
	}
	pipex.paths = ft_find_command(envp);
	if(pipe(pipex.fd) == -1)
	{
		perror("Pipe");
		exit (EXIT_FAILURE);
	}
	pipex.pid[0] = fork();
		-> child process;
	pipex.pid[1] = fork();
		-> child process (2);
	-> free pipex + close fd;
}
