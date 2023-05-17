/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkoletzk <lkoletzk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 10:49:26 by lkoletzk          #+#    #+#             */
/*   Updated: 2023/05/17 15:51:42 by lkoletzk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// MADATORY VERSION
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
}*/

// BONUS VERSION
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
	ft_first_infile(argv, &pipex);
	while (i < argc - 2)
	{
		ft_printf("AAAA\n");
		ft_mid_child_process(&pipex, argv, envp, i);
		i++;
	}
	ft_printf("BBB\n");	
	ft_last_child_process(&pipex, argc, argv, envp);
	ft_printf("ccc\n");
	//wait(NULL);
	while (wait(NULL) > 0)
		;
	return (0);
}

// ERREURS DETECTEES :
// - fd non fermé
