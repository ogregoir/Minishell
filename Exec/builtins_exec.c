/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 16:32:41 by rgreiner          #+#    #+#             */
/*   Updated: 2023/11/21 04:26:16 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_builtin(char *content, int type)
{
	if (ft_strncmp(content, "echo", 4) == 0 && ft_strlen(content) == 4)
		return (0);
	if (ft_strncmp(content, "pwd", 3) == 0 && ft_strlen(content) == 3)
		return (0);
	if (ft_strncmp(content, "export", 6) == 0)
		return (0);
	if (ft_strncmp(content, "unset", 5) == 0)
		return (0);
	if (ft_strncmp(content, "env", 3) == 0 && ft_strlen(content) == 3)
		return (0);
	if (type == 0)
		return (0);
	return (1);
}

void	ft_exec_main(int file, t_lex *lex, t_global *data)
{
	if (ft_strncmp(lex->content, "echo", 4) == 0 && \
		ft_strlen(lex->content) == 4)
		g_error = ft_echo(lex, file);
	else if (ft_strncmp(lex->content, "pwd", 3) == 0 && \
		ft_strlen(lex->content) == 3)
		g_error = ft_pwd(file);
	else if (ft_strncmp(lex->content, "export", 6) == 0)
		g_error = ft_export(lex, data);
	else if (ft_strncmp(lex->content, "unset", 5) == 0)
		g_error = ft_unset(lex, data);
	else if (ft_strncmp(lex->content, "env", 3) == 0 && \
		ft_strlen(lex->content) == 3)
		g_error = ft_env(lex, data, file);
}

void	check_file(t_lex *lex)
{
	t_lex	*tmp;

	tmp = lex;
	while (tmp && tmp->type != 1)
	{
		if (tmp->next && tmp->type >= 2 && tmp->type <= 5 && tmp->type != 4)
		{
			if (access(tmp->next->content, F_OK) != 0)
			{
				if (tmp->type == 3 || tmp->type == 5)
					break ;
				ft_error(tmp->next->content, \
				": No such file or directory", "", 0);
			}
			if (access(tmp->next->content, W_OK | R_OK) != 0)
				ft_error(tmp->next->content, ": Permission denied", "", 0);
		}
		tmp = tmp->next;
	}
}

void	builtin_child(t_lex *lex, int i, int old, t_global *data)
{
	int	file;

	file = 1;
	if (check_redi(lex) == 1)
	{
		file = ft_builtin_redi(lex, file, 1);
		old = dup(STDOUT_FILENO);
		ft_exec_main(file, lex, data);
		close_redi(old, file);
	}
	else
	{
		file = data->fd[i + 1][1];
		ft_exec_main(file, lex, data);
	}
}

t_lex	*ft_builtin_exec(t_global *data, t_lex *lex, int child, int i)
{
	int	file;
	int	old;

	file = 1;
	old = 0;
	if (child == 1)
	{
		builtin_child(lex, i, old, data);
		exit(g_error);
	}
	else
	{
		file = ft_builtin_redi(lex, file, 0);
		old = dup(STDOUT_FILENO);
		ft_exec_main(file, lex, data);
		close_redi(old, file);
	}
	exit(g_error);
	return (lex);
}
