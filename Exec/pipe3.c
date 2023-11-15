/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 02:27:39 by marvin            #+#    #+#             */
/*   Updated: 2023/10/27 02:27:39 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_pipex_in(int **fd, t_lex *lex, t_pipe *data)
{
	lex = lex->next;
	if (open(lex->content, O_RDONLY) == -1)
	{
		ft_error(lex->content, ": No such file or directory", NULL, 1);
		close_pipe(fd, data->pipenbr);
		exit(1);
	}
	dup2(open(lex->content, O_RDONLY), STDIN_FILENO);
}

void	check_dir(t_lex *lex)
{
	DIR	*dir;

	dir = NULL;
	if (lex->type != 8)
		return ;
	dir = opendir(lex->content);
	if (ft_strchri(lex->content, 47) != -1)
	{
		if (access(lex->content, X_OK) != 0)
		{
			ft_error("", lex->content, ": No such file or directory", 1);
			exit(127);
		}
	}
	if (dir)
	{
		ft_error("", lex->content, ": Is a directory", 1);
		closedir(dir);
		exit(126);
	}
	else
		return ;
}

void	ft_pipex_main(int i, t_lex *lex, t_pipe *data, t_global *g)
{
	check_file(lex);
	check_dir(lex);
	if (g->file != 0 && ft_builtin(lex->content, 1) != 0)
	{
		if (lex->next && lex->next->next && lex->next->type == 4)
			lex = lex->next->next;
		if (lex->next == NULL || lex->type == 4)
			dup2(g->file, STDIN_FILENO);
		data->in = 1;
		if (lex->next && lex->next->type == 2)
		{
			if (lex->next->next && lex->next->next->next \
			&& lex->next->next->next->next)
				lex = lex->next->next->next->next;
			if (lex->next && lex->next->type == 4)
			{
				g->file = check_here_doc(lex, g);
				ft_pipex_main(i, lex, data, g);
				return ;
			}
			dup2(g->file, STDIN_FILENO);
			close_pipe(g->fd, data->pipenbr);
			return ;
		}
	}
	if (ft_builtin(lex->content, 1) == 0)
		ft_builtin_exec(g, lex, 0, i);
	if (check_redi(lex) == 1)
	{
		if (ft_builtin(lex->content, 1) == 0)
			ft_builtin_exec(g, lex, 0, i);
		while (g->file == 0 && lex && lex->type == 8)
			lex = lex->next;
		if (lex->type == 2)
		{
			lex = lex->next;
			if (lex == NULL)
			{
				ft_putendl_fd \
				("minishell: syntax error near unexpected token `newline'", 2);
				exit(1);
			}
			if (open(lex->content, O_RDONLY) == -1)
			{
				ft_error(lex->content, ": No such file or directory", "", 1);
				close_pipe(g->fd, data->pipenbr);
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
				ft_putendl_fd \
				("minishell: syntax error near unexpected token `newline'", 2);
				exit(1);
			}
			g->file = openfile(lex->content, 1);
			dup2(g->file, STDOUT_FILENO);
			if (data->in == 0)
				dup2(g->fd[i][0], STDIN_FILENO);
		}
		if (lex->type == 5)
		{
			lex = lex->next;
			if (lex == NULL)
			{
				ft_putendl_fd \
				("minishell: syntax error near unexpected token `newline'", 2);
				exit(1);
			}
			g->file = openfile(lex->content, 0);
			dup2(g->file, STDOUT_FILENO);
			if (data->in == 0)
				dup2(g->fd[i][0], STDIN_FILENO);
		}
		if (lex->next)
		{
			if (lex->next->type == 3 || lex->next->type == \
			5 || lex->next->type == 2 || lex->next->type == 4)
			{
				g->file = check_here_doc(lex, g);
				ft_pipex_main(i, lex->next, data, g);
				return ;
			}
			if (lex->next->type == 8 && lex->type != 4)
				ft_pipex_in(g->fd, lex, data);
		}
	}
	else if (data->in == 0)
		dup2(g->fd[i][0], STDIN_FILENO);
	close_pipe(g->fd, data->pipenbr);
}

void	pipex(t_lex *lex, t_global *datas, int nbrpipe)
{
	pid_t	*pid;
	t_pipe	data;
	int		i;

	i = 0;
	datas->fd = NULL;
	data.pipenbr = nbrpipe;
	data.in = 0;
	datas->file = 0;
	pid = malloc(sizeof(pid_t) * (data.pipenbr + 1));
	datas->fd = create_fd(data.pipenbr, datas->fd);
	ft_pipe_create(data.pipenbr, datas->fd);
	while (lex && i <= data.pipenbr)
	{
		if (lex->type == 1)
			lex = lex->next;
		datas->file = check_here_doc(lex, datas);
		if (datas->file == -1)
			break ;
		pid[i] = fork();
		if (i < data.pipenbr && pid[i] == 0)
			ft_pipex_child(i, lex, &data, datas);
		else if (i == data.pipenbr && pid[i] == 0)
			ft_pipex_main(i, lex, &data, datas);
		if (lex->next && lex->next->next && lex->type == 4)
			lex = lex->next->next;
		if (pid[i] == 0 && ft_builtin(lex->content, 1) != 0)
			datas->error_code = ft_check_cmd(lex, datas);
		while (lex && lex->type != 1)
			lex = lex->next;
		i++;
	}
	close_pipe(datas->fd, data.pipenbr);
	free(pid);
	unlink("temp");
}

int	detect_pipe(t_lex *lex, t_global *data)
{
	int		i;
	int		status;
	int		j;
	t_lex	*tmp;

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
	return (WEXITSTATUS(status));
}
