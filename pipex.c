/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkoletzk <lkoletzk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 14:49:02 by lkoletzk          #+#    #+#             */
/*   Updated: 2023/03/31 12:52:54 by lkoletzk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Votre programme doit se comporter exactement comme la commande shell suivante :
$> < file1 cmd1 | cmd2 > file2
Exemples :
$> ./pipex infile "ls -l" "wc -l" outfile
Devrait être identique à < infile ls -l | wc -l > outfile
$> ./pipex infile "grep a1" "wc -w" outfile
Devrait être identique à < infile grep a1 | wc -w > outfile

BONUS:
• Gérez plusieurs pipes.
$> ./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2
Devrait être identique à < file1 cmd1 | cmd2 | cmd3 ... | cmdn > file2
• Gérez « et » quand le premier paramètre est "here_doc".
$> ./pipex here_doc LIMITER cmd cmd1 file
Devrait être identique à cmd << LIMITER | cmd1 >> file
*/

/*
- 4 arguments, ni plus ni moins (hors bonus)
- arguments dans l'ordre uniquement
- verifier les erreurs : fd existant, droits, "the binary of the command exists"
- le programme effectue ce qu'on lui demande sans information ou etapes
a l'encontre des commandes shell

BONUS :
- le programme gere l'usage de plusieurs pipes l'un apres l'autre
/!| doit gerer autant de pipes que possible (pas uniquement 2 ni 5)
- le progamme peut copier l'utilisation des << et >>
exemple de test : CMD << STOP_VALUE | CMD1 >> file1
*/

# include "pipex.h"

// void	pipex(int fd1, int fd2, char *cmd1, char *cmd2)
// {
// 	int	end[2];
// 	int status;
// 	pid_t child1;
// 	pid_t child2;

// 	pipe(end);
// 	child1 = fork();
// 	if (child1 < 0)
// 		return (perror("Fork: "));
// 	if (child1 == 0)
// 		child_one(fd1, cmd1);
// 	child2 = fork();
// 	if (child2 < 0)
// 		return (perror("Fork: "));
// 	if (child2 == 0)
// 		child_two(fd2, cmd2);
// 	close(end[0]);					// this is the parent
// 	close(end[1]);					// doing nothing
// 	waitpid(child1, &status, 0);	// supervising the children
// 	waitpid(child2, &status, 0);	// while they finish their tasks
// }

static char	**ft_freetab(char **tab)
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

char	*ft_get_command(char **paths, char *cmd)
{
// /!\ faire comme la commande originale avec '' et {}
	char *tmp;
	char *command;
	int	x;

	x = -1;
	while(paths[++x])
	{
		tmp = ft_strjoin(paths[x], "/");
		command = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(command, F_OK | X_OK) == 0) // F_OK -> existing file | X_OK executing permission
			return (command);
		free(command);
	}
	return (NULL);
}

char	**ft_find_command_paths(char **envp)
{
	char	*path_envp;
	char	**paths;
	int	len;
	int	x;

	x = -1;
	len = 0;
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	path_envp = *envp + 5;
	while (path_envp[len] != '\n' && path_envp[len] != '\0')
		len++;
	path_envp = ft_substr(path_envp, 0, len);
	paths = ft_split(path_envp, ':');
	free(path_envp);
	return (paths);
}

void	child_process(t_pipe pipex, char **argv, char **envp)
{
	if (pipex.pid[0] == 0)
	{
		dup2(pipex.fd[1], 1);
		close(pipex.fd[0]);
		pipex.cmd_args = ft_split(argv[2], " ");
		pipex.cmd = ft_get_command(pipex.paths, pipex.cmd_args[0]);
		if (!pipex.cmd)
		{
			error message cmd not found;
			free all
			exit ;
		}
		execve(pipex.cmd, pipex.cmd_args, envp);
		free args + ft_find_command_paths
		perror(strerror(errno));
		close (fd[1]);
		exit(1);
	}
	else
		free?
}



// /!\ Il faut d abord pipe les fd avant de fork pour que les enfants
// puissent heriter des fd
int	main(int argc, char **argv, char **envp)
{
	int	fd[2];

	if (argc != 5)
		return (0);
	fd[0] = open(argv[1], O_RDONLY);
	fd[1] = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	//  int open(const char *pathname, int flags, mode_t mode); 0644 means "rw-r--r--" on chmod of 420 ?
	if (fd[0] < 0 || fd[1] < 0)
	{
		perror("fd");
		exit (EXIT_FAILURE);
	}
	// pipex(fd1, fd2, argv, envp);
	ft_find_command(argc, argv, envp);
	if (access(argv[2], X_OK) == 0 && access(argv[3], X_OK) == 0)
		ft_printf("\"%s\" are accessible commands in executable mode\n",
			argv[2], argv[3]);


	else if (access(argv[2], X_OK) < 0 || access(argv[3], X_OK) < 0)
		ft_printf("Error: one or both commands are not accessible in \
			executable mode %s\n", argv[1], strerror(access(argv[1], X_OK)));

	if (pipe(fd) == -1)
	{
		perror("Pipe");
		exit (EXIT_FAILURE);
	}
	pid_t pid1 = fork();
	if (pid1 == 0)
	{
		close(fd[0]);
		do the cmd1 on infile;
		close (fd[1]);
	}
	else
		...
	pid_t	pid2 = fork();
	if (pid2 == 0)
	{
		close(fd[1]);
		do the cmd2 on outfile;
		close (fd[0]);
	}
	else
		...
	close(fd[0]);
	close(fd[1]);
	return (0);
}


