/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkoletzk <lkoletzk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 17:39:32 by lkoletzk          #+#    #+#             */
/*   Updated: 2023/05/10 17:52:39 by lkoletzk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
	if (argc == 5)
		ft_pipex();
	if (here_doc == 1)
		ft_pipex_heredoc();
	else
		ft_pipex_bonus();
	return (EXIT_SUCCESS);
}
