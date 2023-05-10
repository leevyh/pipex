/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkoletzk <lkoletzk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 15:14:40 by lkoletzk          #+#    #+#             */
/*   Updated: 2023/05/10 17:45:52 by lkoletzk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

/* open, close, write, read, access, dup, dup2, execve, unlink, fork, pipe */
# include <fcntl.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/uio.h>

/* waitpid, wait */
# include <sys/wait.h>

/* malloc, free, exit */
# include <stdlib.h>

/* strerror, perror */
# include <string.h>
# include <stdio.h>
# include <errno.h>

# include "libft/libft.h"

typedef struct s_pipe
{
	char	*cmd;
	char	**paths;
	char	**cmd_args;
	int		fd[2];
	pid_t	pid1;
	pid_t	pid2;
}	t_pipe;

void	ft_perror(char *str, t_pipe pipex);
void	ft_free_all(t_pipe pipex);
char	**ft_freetab(char **tab);

char	**ft_find_command_paths(char **envp);
char	*ft_get_command(char **paths, char **args);

void	ft_1st_child_process(t_pipe pipex, char *argv[], char *envp[]);
void	ft_2nd_child_process(t_pipe pipex, char *argv[], char *envp[]);

#endif
