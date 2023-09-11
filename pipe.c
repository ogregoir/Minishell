/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgreiner <rgreiner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 10:11:22 by rgreiner          #+#    #+#             */
/*   Updated: 2023/09/11 14:58:57 by rgreiner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void	close_pipe(int **fd, int pipenbr)
{
	int	j;

	j = 0;
	while (j <= pipenbr)
	{
		close(fd[j][0]);
		close(fd[j][1]);
		j++;
	}
}

int	**create_fd(int pipenbr, int **fd)
{
	int	i;

	i = 0;
	fd = malloc(sizeof(fd) * pipenbr);
	while (i <= pipenbr)
	{
		fd[i] = malloc(sizeof(*fd) * 2);
		i++;
	}
	return (fd);
}

void	ft_pipe_create(int pipenbr, int **fd)
{
	int	j;

	j = 0;
	while (j <= pipenbr)
	{
		pipe(fd[j]);
		j++;
	}
}

void	ft_pipex_child(int **fd, int pipenbr, int i)
{
	dup2(fd[i][0], STDIN_FILENO);
	dup2(fd[i + 1][1], STDOUT_FILENO);
	close_pipe(fd, pipenbr);
}

void	ft_pipex_child2(int **fd, int pipenbr, int i)
{
	if (i == 0)
	{
		ft_pipex_child(fd, pipenbr, i);
		return ;
	}
	dup2(fd[i][0], STDIN_FILENO);
	dup2(fd[i + 1][1], STDOUT_FILENO);
	close_pipe(fd, pipenbr);
}

void	ft_pipex_main(int **fd, int pipenbr, int i)
{
	dup2(fd[i][0], STDIN_FILENO);
	close_pipe(fd, pipenbr);
}

int	pipex(t_lex *lex, char **envp, int pipenbr)
{
	pid_t	*pid;
	int		**fd;
	int		i;
	int		ret;

	i = 0;
	fd = NULL;
	pipenbr = pipenbr;
	pid = malloc(sizeof(pid_t) * pipenbr + 1);
	fd = create_fd(pipenbr, fd);
	ft_pipe_create(pipenbr, fd);
	while (i <= pipenbr)
	{
		if(lex->type == 1)
			lex = lex->next;
		pid[i] = fork();
		if (i < pipenbr && pid[i] == 0)
			ft_pipex_child2(fd, pipenbr, i);
		else if (i == pipenbr && pid[i] == 0)
			ft_pipex_main(fd, pipenbr, i);
		if (pid[i] == 0)
			ret = ft_check_cmd(lex, envp);
		i++;
		if(lex->next == NULL)
			break;
		while(lex && lex->type != 1)
			lex = lex->next;
	}
	close_pipe(fd, pipenbr);
	while (wait(0) > 0)
		;
	return(ret);
}

int detect_pipe(t_lex *lex, char **envp)
{
	int i;
    t_lex *tmp;
    
    tmp =  lex;
	i = 0;
	while(tmp->next)
	{
		if(tmp->type == 1)
			i++;
		tmp = tmp->next;
    }
	if(i > 0)
		{
			error_code = pipex(lex, envp, i);
			return (1);
		}
	return(0) ;
}
