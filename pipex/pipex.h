/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkoletzk <lkoletzk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 15:14:40 by lkoletzk          #+#    #+#             */
/*   Updated: 2023/06/02 13:28:07 by lkoletzk         ###   ########.fr       */
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

/* PARTIE MANDATAIRE */
typedef struct s_pipe_m
{
	int		fd[2];
	pid_t	pid;
}	t_pipe_m;

/* Fonctions de gestion */
void	ft_perror(char *str);
char	**ft_freetab(char **tab);
void	ft_close_fds(int fd[]);
void	ft_child_error(char **cmd_args, char **paths);

char	**ft_find_command_paths(char *envp[]);
char	*ft_get_command(char **paths, char **args);
void	ft_execve(char *argv, char *envp[]);

void	ft_first_child_process(t_pipe_m *pipex, char **argv, char *envp[]);
void	ft_last_child_process(t_pipe_m *pipex, int argc, char **argv,
			char *envp[]);

/* PARTIE BONUS */
typedef struct s_pipe_b
{
	int		infile;
	int		outfile;
}	t_pipe_b;

int		ft_here_doc(int argc, char **argv);
void	ft_1st_input(char **argv, t_pipe_b *pipex);
void	ft_save_output(t_pipe_b *pipex, int fd[]);
void	ft_child_processes(t_pipe_b *pipex, char **argv, char *envp[], int i);
void	ft_last_process(t_pipe_b *pipex, int argc, char **argv,
			char *envp[]);

#endif
