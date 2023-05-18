/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkoletzk <lkoletzk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 10:18:33 by lkoletzk          #+#    #+#             */
/*   Updated: 2023/05/18 12:10:35 by lkoletzk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

/* FT_FIND_COMMAND_PATHS:
1- Cherche PATH dans l'environnement
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

/* FT_GET_COMMAND:
1- Verifie si le path (/usr/bin/cmd) n'est pas deja donne
2- Cherche le path dans l'env
3- Verifie si la commande existe et peut s'executer 
via F_OK: existing file | X_OK: executing permission
4- Renvoie la commande */
char	*ft_get_command(char **paths, char **cmd_args)
{
	char	*tmp;
	char	*command;
	int		x;

	if (!ft_strncmp("/", cmd_args[0], 0) && !access(cmd_args[0], F_OK | X_OK))
		return (cmd_args[0]);
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
