/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkoletzk <lkoletzk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 15:14:40 by lkoletzk          #+#    #+#             */
/*   Updated: 2023/03/31 12:40:44 by lkoletzk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

/* open, close, write, read, access, dup, dup2, execve, unlink, fork, pipe */
# include <unistd.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <fcntl.h>

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
	pid_t	pid[2];
}	t_pipe;

char	**ft_find_command_paths(char **envp);

#endif
