/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkoletzk <lkoletzk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 17:39:32 by lkoletzk          #+#    #+#             */
/*   Updated: 2023/05/16 09:53:51 by lkoletzk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipe	pipex;


	if (argc >= 5)
		ft_here_doc(argv); 

	if (argc < 5)
	{
		write(2, "Unvalid number of arguments\n", 28);
		exit(EXIT_FAILURE);
	}
	if (argc == 5)
		ft_pipex();
	if (here_doc == 1)
		ft_pipex_heredoc();
	else
		ft_pipex_bonus();
	return (EXIT_SUCCESS);
}
