/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkoletzk <lkoletzk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 14:49:02 by lkoletzk          #+#    #+#             */
/*   Updated: 2023/05/11 17:00:23 by lkoletzk         ###   ########.fr       */
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

/* 1- Verifie si le path (usr/bin/cmd)n'est pas deja donne
2- Cherche le path dans l'env
3- Verifie si la commande existe et peut s'executer 
via F_OK: existing file | X_OK: executing permission
4- Renvoie la commande */
char	*ft_get_command(char **paths, char **cmd_args)
{
	char	*tmp;
	char	*command;
	int		x;

	if (!ft_strncmp("/", cmd_args[0], 0) && access(cmd_args[0], F_OK | X_OK) == 0)
		return(cmd_args[0]);
	else
	{
		x = -1;
		while(paths[++x])
		{
			tmp = ft_strjoin(paths[x], "/");
			if (!tmp)
				return (NULL);
			command = ft_strjoin(tmp, cmd_args[0]);
			free(tmp);
			if (!command)
				return (NULL);
			if (access(command, F_OK | X_OK) == 0)
				return(command);
			free(command);	
		}
	}
	return (NULL);
}

/* 1- Cherche PATH dans l'environnement
2- Copie tout le PATH dans la variable path_envp
3- Separe les differentes adresses a chaque ':' */
char	**ft_find_command_paths(char **envp)
{
	char	*path_envp;
	char	**paths;
	int		len;

	len = 0;
	if (!envp[0])
		return (NULL);
	while (ft_strncmp("PATH=", *envp, 5))
		envp++;
	*envp = *envp + 5;
	while (envp[0][len] != '\n' && envp[0][len] != '\0')
		len++;
	path_envp = ft_substr(envp[0], 0, len);
	if (!path_envp)
		return (NULL);
	paths = ft_split(path_envp, ':');
	free(path_envp);
	if (!paths)
		return (ft_freetab(paths));
	return (paths);
}

/* 1- Recupere la commande et ses arguments et les split
3- Recupere le chemin de la commande
4- Execute la commande */
void	ft_execve(char *argv, char **envp)
{
	char	**paths;
	char	**cmd_args;
	char	*cmd;
	
	paths = ft_find_command_paths(envp);
	cmd_args = ft_split(argv, ' ');
	if (!cmd_args)		
		exit(EXIT_FAILURE);
	cmd = ft_get_command(paths, cmd_args);
	if (!cmd || execve(cmd, cmd_args, envp) == -1)
	{
		ft_putstr_fd("command not found: ", 2);
		ft_putendl_fd(cmd_args[0], 2);
		ft_freetab(paths);
		ft_freetab(cmd_args);
		if (cmd)
			free(cmd);
		exit(EXIT_FAILURE);
	}
}

void	ft_1st_child_process(t_pipe pipex, char **argv, char **envp)
{
	int	infile;
	
	infile = open(argv[1], O_RDONLY);
	if (infile < 0)
		ft_perror("fd");
	dup2(infile, STDIN_FILENO);
	close(infile);
	dup2(pipex.fd[1], STDOUT_FILENO);
	close(pipex.fd[0]);
	close(pipex.fd[1]);
	if (!ft_strncmp("here_doc", argv[1], 8))
		ft_execve(argv[3], envp);
	else
		ft_execve(argv[2], envp);
}

void	ft_last_child_process(t_pipe pipex, int argc, char **argv, char **envp)
{
	int	outfile;

	outfile = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (outfile < 0)
		ft_perror("fd");
	dup2(outfile, STDOUT_FILENO);
	close(outfile);
	dup2(pipex.fd[0], STDIN_FILENO);
	close(pipex.fd[0]);
	close(pipex.fd[1]);
	ft_execve(argv[3], envp);
}