/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 15:18:39 by rgreiner          #+#    #+#             */
/*   Updated: 2023/10/23 17:45:08 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int		check_redi_in(t_lex *lex)
{
	t_lex *tmp;

	tmp = lex;
	while(tmp)
	{
		if(tmp->type == 2)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	ft_pipex_child(int **fd, int i, t_lex *lex, t_pipe *data, t_global *global)
{
	int file;
	
	if(ft_builtin(lex->content, 1) == 0)
			ft_builtin_exec(global, lex, 1, fd, i);
	if(check_redi(lex) == 1)
	{
	if(ft_builtin(lex->content, 1) == 0)
		ft_builtin_exec(global, lex, 1, fd, i);
	while(lex && lex->type == 8)
		lex = lex->next;
	if(lex->next && lex->type == 2)
		{
			lex = lex->next;
			if(open(lex->content, O_RDONLY) == -1)
			{
				ft_error(lex->content, ": No such file or directory", NULL, 1);
				close_pipe(fd, data->pipenbr);
				exit(1);
			}
			dup2(open(lex->content, O_RDONLY), STDIN_FILENO);
			dup2(fd[i + 1][1], STDOUT_FILENO);
			data->in = 1;
		}
		if(lex->type == 3)
		{
			lex = lex->next;
			file = openfile(lex->content, 1);
			dup2(file ,STDOUT_FILENO);
			if(data-> in == 0)
				dup2(fd[i][0], STDIN_FILENO);
		}
		if (lex->type == 4)
		{
			file = ft_here_doc_open(lex, 0);
			lex = lex->next;
			if(lex->next && lex->next->type == 1)
				dup2(file, STDIN_FILENO);
		}
		if(lex->type == 5)
		{
			lex = lex->next;
			file = openfile(lex->content, 0);
			dup2(file ,STDOUT_FILENO);
			if (data-> in == 0)
				dup2(fd[i][0], STDIN_FILENO);
		}
		if(lex->next)
		{
		if(lex->next->type == 3 || lex->next->type == 5 || lex->next->type == 2 || lex->type == 2 || lex->next->type == 4)
			ft_pipex_child(fd, i, lex, data, global);
		}
	}
	else if(i != 0)
		dup2(fd[i][0], STDIN_FILENO);
	dup2(fd[i + 1][1], STDOUT_FILENO);
	close_pipe(fd, data->pipenbr);
}