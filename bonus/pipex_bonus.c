/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkoletzk <lkoletzk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 17:42:37 by lkoletzk          #+#    #+#             */
/*   Updated: 2023/06/21 17:02:24 by lkoletzk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	ft_here_doc(int argc, char **argv)
{
	int		fd;
	char	*line;

	if (!ft_strncmp("here_doc", argv[1], 9) && argc > 5)
	{
		write(1, "pipe here_doc> ", 15);
		line = get_next_line(0);
		fd = open("here_doc", O_RDWR | O_CREAT | O_APPEND, 0777);
		while (line)
		{
			if (!ft_strncmp(argv[2], line, ft_strlen(argv[2]))
				&& line[ft_strlen(argv[2])] == '\n')
				break ;
			write(1, "pipe here_doc> ", 15);
			ft_putstr_fd(line, fd);
			free(line);
			line = get_next_line(0);
		}
		free(line);
		close(fd);
		return (1);
	}
	return (0);
}

void	ft_1st_input(char **argv, t_pipe_b *pipex)
{
	pipex->infile = open(argv[1], O_RDONLY);
	if (pipex->infile == -1)
		perror("open");
}

void	ft_save_output(t_pipe_b *pipex, int fd[])
{
	if (pipex->infile != -1)
		close (pipex->infile);
	pipex->infile = fd[0];
	close(fd[1]);
}

void	ft_child_processes(t_pipe_b *pipex, char **argv, char **envp, int i)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		ft_perror("Pipe");
	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (pid == 0)
	{
		if (pipex->infile == -1)
		{
			ft_close_fds(fd);
			exit(EXIT_FAILURE);
		}
		dup2(pipex->infile, STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		ft_close_fds(fd);
		close(pipex->infile);
		ft_execve(argv[i], envp);
	}
	else
		ft_save_output(pipex, fd);
}

void	ft_last_process(t_pipe_b *pipex, int argc, char **argv,
	char *envp[])
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (pid == 0)
	{
		pipex->outfile = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (pipex->outfile < 0)
			ft_perror("fd");
		dup2(pipex->outfile, STDOUT_FILENO);
		close(pipex->outfile);
		dup2(pipex->infile, STDIN_FILENO);
		close(pipex->outfile);
		close(pipex->infile);
		ft_execve(argv[argc - 2], envp);
	}
	else
		close(pipex->infile);
}
