/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkoletzk <lkoletzk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 12:27:17 by lkoletzk          #+#    #+#             */
/*   Updated: 2023/05/10 16:59:06 by lkoletzk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "pipex.h"

void	ft_free_all(t_pipe pipex)
{
	int	i;

	i = -1;
	while (pipex.paths[++i])
		free(pipex.paths[i]);
	free(pipex.paths);
	// if (pipex.cmd)
	// 	free(pipex.cmd);
	// if (pipex.cmd_args)
	// {
	// 	i = -1;
	// 	while (pipex.cmd_args[++i])
	// 		free(pipex.cmd_args[i]);
	// 	free(pipex.cmd_args);
	// }
}

void	ft_perror(char *str, t_pipe pipex)
{
	(void)pipex;
	perror(str);
	// ft_free_all(pipex);
	exit(EXIT_FAILURE);
}

char	**ft_freetab(char **tab)
{
	int	x;

	x = 0;
	while (tab[x])
	{
		free(tab[x]);
		x++;
	}
	free(tab);
	return (NULL);
}
