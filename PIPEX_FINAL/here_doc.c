/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkoletzk <lkoletzk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 17:42:37 by lkoletzk          #+#    #+#             */
/*   Updated: 2023/05/11 18:37:30 by lkoletzk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "pipex.h"

/* Function who make a child process that will read from the stdin with
 get_next_line until it find the limiter word and then put the output inside a
 pipe. The main process will change his stdin for the pipe file descriptor. */
void    ft_here_doc(char **argv)
{
	int     fd;
    char    *line;

   if (!ft_strncmp("here_doc", argv[1], 9))
    {
        line = get_next_line(0);
        fd = open("here_doc", O_RDWR | O_CREAT, 0777);
        while (line)
        {
            if (!ft_strncmp(argv[2], line, ft_strlen(argv[2])))
                break;
            ft_putstr_fd(line, fd);
            free(line);
            line = get_next_line(0);
        }
        free(line);
        argv[1] = "here_doc";
        close(fd);
    }
}

// void    ft_close_fds(t_pipe pipex, int i)
// {
//     close(pipex.fd[i][0]);
//     close(pipex.fd[i][1]);
    
// }

// void	ft_mid_child_process(t_pipe pipex, char **argv, char **envp)
// {
// 	dup2(pipex.fd[i][0], STDIN_FILENO);
// 	dup2(pipex.fd[i+1][1], STDOUT_FILENO);
// 	ft_close_fds(pipex, i);
//     ft_close_fds(pipex, i+1);
// 	ft_execve(argv[2], envp);
// }
// {
//     t_pipe  *pfd;
//     int i;

//     i = -1;
//     pfd = ft_calloc(sizeof(t_pipe));
//     if ((argc - 4) > 256) // si + de 1024 fd
//     {
//         write(2, "Error in allocating memory\n", 28);
//         free(fd);
//         exit(EXIT_FAILURE);
//     }
//     pipex.fd = (int **)ft_calloc(sizeof(int *) * (argc - 4));
//     while (++i < (argc - 4))
//         pipex.fd[i] = (int *)ft_calloc(sizeof(int) * 2);
// }

// on cree un t_pipe
// on malloc autant de fd que le nombre de pipes
// on malloc les fds *2

// int main(int argc, char **argv)
// {
//     if (argc >= 5)
//         ft_here_doc(argv);
    
//     int i = -1;
//     while(argv[++i])
//         ft_printf(argv[i]);
//     return (0);
// }
