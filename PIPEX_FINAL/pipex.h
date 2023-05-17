/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkoletzk <lkoletzk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 15:14:40 by lkoletzk          #+#    #+#             */
/*   Updated: 2023/05/17 14:03:50 by lkoletzk         ###   ########.fr       */
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
	int		fd[2];
	pid_t	pid;
}	t_pipe;

void	ft_perror(char *str);
char	**ft_freetab(char **tab);
void	ft_close_fds(int fd[]);

char	**ft_find_command_paths(char **envp);
char	*ft_get_command(char **paths, char **args);

void	ft_1st_child_process(t_pipe *pipex, char **argv, char *envp[], int i);
void	ft_mid_child_process(t_pipe *pipex, char **argv, char *envp[], int i);
void	ft_last_child_process(t_pipe *pipex, int argc, char **argv, char *envp[]);

int		ft_here_doc(int argc, char **argv);

#endif
