/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkoletzk <lkoletzk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 10:18:33 by lkoletzk          #+#    #+#             */
/*   Updated: 2023/06/02 13:49:39 by lkoletzk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

/* FT_FIND_COMMAND_PATHS:
1- Cherche PATH dans l'environnement
2- Copie tout le PATH dans la variable path_envp
3- Separe les differentes adresses a chaque ':' */
char	**ft_find_command_paths(char **envp)
{
	char	**paths;
	int		len;

	len = 0;
	if (!*envp)
		return (NULL);
	while (*envp)
	{
		if (ft_strncmp("PATH", *envp, 4) == 0)
		{
			paths = ft_split(*envp + 5, ':');
			if (!*paths)
				return (NULL);
			return (paths);
		}
		envp++;
	}
	return (NULL);
}

char	*ft_find_absolut_path(char **paths, char **cmd_args)
{
	if (!paths && ft_strchr(cmd_args[0], '/') != NULL)
	{
		if (access(cmd_args[0], F_OK | X_OK) == 0)
			return (cmd_args[0]);
	}
	if (paths && access(cmd_args[0], F_OK | X_OK) == 0)
	{
		ft_freetab(paths);
		return (cmd_args[0]);
	}
	else
		ft_child_error(cmd_args, paths);
	return (NULL);
}

/* FT_GET_COMMAND:
1- Verifie si l'absolut path (/usr/bin/cmd) n'est pas déja donné
2- Verifie si la commande existe et peut s'executer 
via F_OK: existing file | X_OK: executing permission
4- Renvoie la commande */
char	*ft_get_command(char **paths, char **cmd_args)
{
	char	*tmp;
	char	*command;
	int		x;

	if (!paths || ft_strchr(cmd_args[0], '/') != NULL)
		return (ft_find_absolut_path(paths, cmd_args));
	else
	{
		x = -1;
		while (paths[++x])
		{
			tmp = ft_strjoin(paths[x], "/");
			if (!tmp)
				return (NULL);
			command = ft_strjoin(tmp, cmd_args[0]);
			free(tmp);
			if (!command)
				return (NULL);
			if (access(command, F_OK | X_OK) == 0)
				return (command);
			free(command);
		}
	}
	return (NULL);
}

/* FT_EXECVE:
1- Recupere la commande et ses arguments et les split
3- Recupere le chemin de la commande
4- Execute la commande */
void	ft_execve(char *argv, char **envp)
{
	char	**paths;
	char	**cmd_args;
	char	*cmd;

	if (argv[0] == '\0' || argv[0] == ' ')
	{
		ft_putstr_fd("command not found\n", 2);
		exit(EXIT_FAILURE);
	}
	cmd_args = ft_split(argv, ' ');
	if (!cmd_args)
		exit(EXIT_FAILURE);
	paths = ft_find_command_paths(envp);
	cmd = ft_get_command(paths, cmd_args);
	if (!cmd || execve(cmd, cmd_args, envp) == -1)
	{
		ft_putstr_fd("command not found: ", 2);
		ft_putendl_fd(cmd_args[0], 2);
		if (paths)
			ft_freetab(paths);
		ft_freetab(cmd_args);
		if (cmd)
			free(cmd);
		exit(EXIT_FAILURE);
	}
}
