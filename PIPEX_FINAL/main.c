/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkoletzk <lkoletzk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 10:49:26 by lkoletzk          #+#    #+#             */
/*   Updated: 2023/05/12 16:47:58 by lkoletzk         ###   ########.fr       */
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
		ft_here_doc(argv); // Check si le premier arg est "here_doc"

	if(pipe(pipex.fd) == -1)
		ft_perror("Pipe");
	pipex.pid1 = fork();
	if (pipex.pid1 == -1)
		exit(EXIT_FAILURE);
	if (pipex.pid1 == 0)
		ft_1st_child_process(pipex, argv, envp);

	// pid_t	pid3;
	// pid3 = fork();
	// if (pid3 == -1)
	// 	exit(EXIT_FAILURE);
	// if (pid3 == 0)
	// 	ft_mid_child_process(pipex, argv, envp, argc - 4);	// on envoie le nombre d'arguments - infile/outfile/cmd1/lastcmd

	pipex.pid2 = fork();
	if (pipex.pid2 == -1)
		exit(EXIT_FAILURE);
	if (pipex.pid2 == 0)
		ft_last_child_process(pipex, argc, argv, envp);

	close(pipex.fd[0]);
	close(pipex.fd[1]);
	wait(NULL);
	// waitpid(pipex.pid1, NULL, 0);
	// waitpid(pipex.pid2, NULL, 0);
	return (0);
}


// {
// 	t_pipe	*pfd;
// 	int i;

// 	i = -1;
// 	pfd = ft_calloc(sizeof(t_pipe));
// 	if ((argc - 4) > 256) // si + de 1024 fd
// 	{
// 		write(2, "Error in allocating memory\n", 28);
// 		free(fd);
// 		exit(EXIT_FAILURE);
// 	}
// 	pipex.fd = (int **)ft_calloc(sizeof(int *) * (argc - 4));
// 	while (++i < (argc - 4))
// 	pipex.fd[i] = (int *)ft_calloc(sizeof(int) * 2);
// }

// on cree un t_pipe
// on malloc autant de fd que le nombre de pipes
// on malloc les fds *2
