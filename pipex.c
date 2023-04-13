/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkoletzk <lkoletzk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 14:49:02 by lkoletzk          #+#    #+#             */
/*   Updated: 2023/04/13 16:13:17 by lkoletzk         ###   ########.fr       */
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


// static char	**ft_freetab(char **tab)
// {
// 	int	x;

// 	x = 0;
// 	while (tab[x])
// 	{
// 		free(tab[x]);
// 		x++;
// 	}
// 	free(tab);
// 	return (NULL);
// }

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
	return (cmd);
}

char	**ft_find_command_paths(char **envp)
{
	char	*path_envp;
	char	**paths;
	int	len;

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

void	ft_1st_child_process(t_pipe pipex, char **argv, char **envp)
{
	dup2(pipex.p_fd[1], 1);
	close(pipex.p_fd[0]);
	dup2(pipex.in, 0);
	pipex.cmd_args = ft_split(argv[2], ' ');
	pipex.cmd = ft_get_command(pipex.paths, pipex.cmd_args[0]);
	if (!pipex.cmd)
	{
		cmd_args_free(&pipex);
		message("Command not found\n");
		cmd_paths_free(&pipex);
		exit(EXIT_FAILURE);
	}
	execve(pipex.cmd, pipex.cmd_args, envp);
	cmd_args_free(&pipex);
	cmd_paths_free(&pipex);
	perror(strerror(errno));
	exit(1);
}

void	ft_2nd_child_process(t_pipe pipex, char **argv, char **envp)
{
	dup2(pipex.p_fd[0], 0);
	close(pipex.p_fd[1]);
	dup2(pipex.out, 1);
	pipex.cmd_args = ft_split(argv[3], ' ');
	pipex.cmd = ft_get_command(pipex.paths, pipex.cmd_args[0]);
	if (!pipex.cmd)
	{
		cmd_args_free(&pipex);
		message("Command not found\n");
		cmd_paths_free(&pipex);
		exit(EXIT_FAILURE);
	}
	execve(pipex.cmd, pipex.cmd_args, envp);
	cmd_args_free(&pipex);
	cmd_paths_free(&pipex);
	perror(strerror(errno));
	exit(1);
}

int	message(char *message)
{
	write(2, message, ft_strlen(message));
	return (1);
}

void	error_message(char *message, int state)
{
	if (!state)
		return ;
	perror(message);
	exit(1);
}

void	cmd_paths_free(t_pipe *pipex)
{
	int		i;

	i = 0;
	close(pipex->in);
	close(pipex->out);
	while (pipex->paths[i])
		free(pipex->paths[i++]);
	free(pipex->paths);
}

void	cmd_args_free(t_pipe *pipex)
{
	int	i;

	i = 0;
	while (pipex->cmd_args[i])
		free(pipex->cmd_args[i++]);
	free(pipex->cmd_args);
	free(pipex->cmd);
}