/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkoletzk <lkoletzk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 14:49:02 by lkoletzk          #+#    #+#             */
/*   Updated: 2023/06/02 11:46:21 by lkoletzk         ###   ########.fr       */
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

#include "../pipex.h"

void	ft_first_child_process(t_pipe_m *pipex, char **argv, char *envp[])
{
	int	infile;

	pipex->pid = fork();
	if (pipex->pid == -1)
		ft_perror("fork");
	if (pipex->pid == 0)
	{
		infile = open(argv[1], O_RDONLY);
		if (infile < 0)
		{
			ft_close_fds(pipex->fd);
			ft_perror("infile");
		}
		dup2(infile, STDIN_FILENO);
		close(infile);
		dup2(pipex->fd[1], STDOUT_FILENO);
		ft_close_fds(pipex->fd);
		ft_execve(argv[2], envp);
	}
}

void	ft_last_child_process(t_pipe_m *pipex, int argc, char **argv,
	char *envp[])
{
	int	outfile;

	pipex->pid = fork();
	if (pipex->pid == -1)
		ft_perror("fork");
	if (pipex->pid == 0)
	{
		outfile = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (outfile < 0)
		{
			ft_close_fds(pipex->fd);
			ft_perror("outfile");
		}
		dup2(outfile, STDOUT_FILENO);
		close(outfile);
		dup2(pipex->fd[0], STDIN_FILENO);
		ft_close_fds(pipex->fd);
		ft_execve(argv[argc - 2], envp);
	}
}
