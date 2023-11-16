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

void	exec_here_doc(t_lex *lex, t_global *g, int i, t_pipe *data)
{
	if (lex->next && lex->next->next && lex->next->type == 4)
		lex = lex->next->next;
	if (lex->next == NULL || lex->type == 4)
		dup2(g->file, STDIN_FILENO);
	data->in = 1;
	if (lex->next && lex->next->type == 4)
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
	}
	g->file = 0;
	ft_pipex_main(i, lex, data, g);
}

void	pipe_main_redi2(t_lex **lex, t_global *g, t_pipe *data, int i)
{
	if ((*lex)->type == 3)
	{
		(*lex) = (*lex)->next;
		if ((*lex) == NULL)
		{
			endl("minishell: syntax error near unexpected token `newline'", 2);
			exit(1);
		}
		g->file = openfile((*lex)->content, 1);
		dup2(g->file, STDOUT_FILENO);
	}
	if ((*lex)->type == 5)
	{
		(*lex) = (*lex)->next;
		if ((*lex) == NULL)
		{
			endl("minishell: syntax error near unexpected token `newline'", 2);
			exit(1);
		}
		g->file = openfile((*lex)->content, 0);
		dup2(g->file, STDOUT_FILENO);
	}
	if (data->in == 0)
		dup2(g->fd[i][0], STDIN_FILENO);
}

void	pipe_main_redi(t_lex **lex, int i, t_pipe *data, t_global *g)
{
	if (ft_builtin((*lex)->content, 1) == 0)
		ft_builtin_exec(g, (*lex), 0, i);
	while (g->file == 0 && (*lex) && (*lex)->type == 8)
		(*lex) = (*lex)->next;
	if ((*lex)->type == 2)
	{
		(*lex) = (*lex)->next;
		if ((*lex) == NULL)
		{
			ft_putendl_fd \
			("minishell: syntax error near unexpected token `newline'", 2);
			exit(1);
		}
		if (open((*lex)->content, O_RDONLY) == -1)
		{
			ft_error((*lex)->content, ": No such file or directory", "", 1);
			close_pipe(g->fd, data->pipenbr);
			exit(1);
		}
		dup2(open((*lex)->content, O_RDONLY), STDIN_FILENO);
		data->in = 1;
	}
	if ((*lex)->type == 3 || (*lex)->type == 5)
		pipe_main_redi2(lex, g, data, i);
}

void	ft_pipex_main(int i, t_lex *lex, t_pipe *data, t_global *g)
{
	check_file(lex);
	check_dir(lex);
	if (g->file != 0 && ft_builtin(lex->content, 1) != 0)
		return (exec_here_doc(lex, g, i, data));
	if (ft_builtin(lex->content, 1) == 0)
		ft_builtin_exec(g, lex, 0, i);
	if (check_redi(lex) == 1)
	{
		pipe_main_redi(&lex, i, data, g);
		if (lex->next)
		{
			if (lex->next->type == 3 || lex->next->type == 5 \
			|| lex->next->type == 2 || lex->next->type == 4)
			{
				g->file = check_here_doc(lex, g);
				ft_pipex_main(i, lex->next, data, g);
				return ;
			}
			if (lex->next->type == 8 && lex->type != 4)
				ft_pipex_in(g->fd, lex, data);
		}
	}
	else if (data->in == 0 && i > 0)
		dup2(g->fd[i][0], STDIN_FILENO);
	close_pipe(g->fd, data->pipenbr);
}
