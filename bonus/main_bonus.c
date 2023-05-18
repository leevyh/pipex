/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkoletzk <lkoletzk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 10:43:01 by lkoletzk          #+#    #+#             */
/*   Updated: 2023/05/18 12:04:21 by lkoletzk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int			i;
	t_pipe_b	pipex;

	if (argc < 5)
	{
		write(2, "Error: Unvalid number of arguments\n", 36);
		exit(EXIT_FAILURE);
	}
	i = 2;
	if (ft_here_doc(argc, argv) > 0)
		i = 3;
	ft_1st_input(argv, &pipex);
	while (i < argc - 2)
	{
		ft_child_processes(&pipex, argv, envp, i);
		i++;
	}
	ft_last_child_process(&pipex, argc, argv, envp);
	while (wait(NULL) > 0)
		;
	return (0);
}

// ERREURS DETECTEES :
// - fd non fermé
