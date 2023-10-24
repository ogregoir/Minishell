/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgreiner <rgreiner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 10:11:22 by rgreiner          #+#    #+#             */
/*   Updated: 2023/10/23 09:03:02 by rgreiner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_redi_out(t_lex *lex)
{
	t_lex *tmp;

	tmp = lex;
	while (tmp)
	{
		if (tmp->type == 3 || tmp->type == 5)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int check_redi(t_lex *lex)
{
	t_lex *tmp;

	tmp = lex;
	while (tmp)
	{
		if (tmp->type == 3 || tmp->type == 5 || tmp->type == 2 || tmp->type == 4)
			return (1);
		if (tmp->type == 1)
			return (0);
		tmp = tmp->next;
	}
	return (0);
}

int openfile(char *content, int mod)
{
	int file;

	if (mod == 0)
		file = open(content, O_APPEND | O_WRONLY | O_CREAT, 0644);
	if (mod == 1)
		file = open(content, O_TRUNC | O_WRONLY | O_CREAT, 0644);
	if (file < 0)
		ft_error(content, ": Permission denied", 0);
	return (file);
}

void ft_pipex_in(int **fd, t_lex *lex, t_pipe *data)
{
	lex = lex->next;
	if (open(lex->content, O_RDONLY) == -1)
	{
		ft_error(lex->content, ": No such file or directory", 1);
		close_pipe(fd, data->pipenbr);
		exit(1);
	}
	dup2(open(lex->content, O_RDONLY), STDIN_FILENO);
}

void ft_pipex_main(int **fd, int i, t_lex *lex, t_pipe *data, t_global *global)
{
	int file;

	file = 0;
	if (ft_builtin(lex->content, 1) == 0)
		ft_builtin_exec(global, lex, 0, fd, i);
	if (check_redi(lex) == 1)
	{
		if (ft_builtin(lex->content, 1) == 0)
			ft_builtin_exec(global, lex, 0, fd, i);
		while (lex && lex->type == 8)
			lex = lex->next;
		if (lex->type == 4)
		{
			file = ft_here_doc_open(lex, 0);
			lex = lex->next;
			if (!lex->next)
				dup2(file, STDIN_FILENO);
		}
		if (lex->type == 2)
		{
			lex = lex->next;
			if (lex == NULL)
			{
				ft_putendl_fd("minishell: syntax error near unexpected token `newline'", 2);
				exit(1);
			}
			if (open(lex->content, O_RDONLY) == -1)
			{
				ft_error(lex->content, ": No such file or directory", 1);
				close_pipe(fd, data->pipenbr);
				exit(1);
			}
			dup2(open(lex->content, O_RDONLY), STDIN_FILENO);
			data->in = 1;
		}
		if (lex->type == 3)
		{
			lex = lex->next;
			if (lex == NULL)
			{
				ft_putendl_fd("minishell: syntax error near unexpected token `newline'", 2);
				exit(1);
			}
			file = openfile(lex->content, 1);
			dup2(file, STDOUT_FILENO);
			if (data->in == 0)
				dup2(fd[i][0], STDIN_FILENO);
		}
		if (lex->type == 5)
		{
			lex = lex->next;
			if (lex == NULL)
			{
				ft_putendl_fd("minishell: syntax error near unexpected token `newline'", 2);
				exit(1);
			}
			file = openfile(lex->content, 0);
			dup2(file, STDOUT_FILENO);
			if (data->in == 0)
				dup2(fd[i][0], STDIN_FILENO);
		}
		if (lex->next)
		{
			if (lex->next->type == 3 || lex->next->type == 5 || lex->next->type == 2 || lex->type == 2 || lex->next->type == 4)
				ft_pipex_main(fd, i, lex, data, global);
			if (lex->next->type == 8)
				ft_pipex_in(fd, lex, data);
		}
	}
	else if(i != 0)
		dup2(fd[i][0], STDIN_FILENO);
	close_pipe(fd, data->pipenbr);
}

void ft_close_main(int **fd, int pipenbr)
{
	int j;

	j = 0;
	while (j < pipenbr)
	{
		close(fd[j][0]);
		close(fd[j][1]);
		j++;
	}
	close(fd[j][0]);
}

void pipex(t_lex *lex, t_global *datas, int nbrpipe)
{
	pid_t *pid;
	t_pipe data;
	int **fd;
	int i;

	i = 0;
	fd = NULL;
	data.pipenbr = nbrpipe;
	data.in = 0;
	pid = malloc(sizeof(pid_t) * (data.pipenbr + 1));
	fd = create_fd(data.pipenbr, fd);
	ft_pipe_create(data.pipenbr, fd);
	while (i <= data.pipenbr)
	{
		if (lex->type == 1)
			lex = lex->next;
		pid[i] = fork();
		if (i < data.pipenbr && pid[i] == 0)
			ft_pipex_child(fd, i, lex, &data, datas);
		else if (i == data.pipenbr && pid[i] == 0)
			ft_pipex_main(fd, i, lex, &data, datas);
		if (pid[i] == 0 && ft_builtin(lex->content, 1) != 0)
			datas->error_code = ft_check_cmd(lex, datas);
		i++;
		if (lex->next == NULL)
			break;
		while (lex && lex->type != 1)
			lex = lex->next;
	}
	close_pipe(fd, data.pipenbr);
	unlink("temp");
}

int detect_pipe(t_lex *lex, t_global *data)
{
	int i;
	int status;
	int j;
	t_lex *tmp;

	tmp = lex;
	status = 0;
	i = 0;
	j = 0;
	while (tmp)
	{
		if (tmp->type == 1)
			i++;
		if (tmp->type > 1 && tmp->type != 8 && tmp->type != 0)
			j++;
		tmp = tmp->next;
	}
	pipex(lex, data, i);
	while (wait(&status) > 0)
		;
	return(WEXITSTATUS(status));

}
