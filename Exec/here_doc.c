/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgreiner <rgreiner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 09:37:09 by rgreiner          #+#    #+#             */
/*   Updated: 2023/11/13 22:44:04 by rgreiner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_here_doc_open2(char *line, int temp, char *cmp)
{
	if (line != NULL)
	{
		if (ft_strcmp(line, cmp) == 0)
			return (0);
		if (ft_strlen(line) > 1 && getenv(line + 1) != NULL)
			temp = ft_create_tmp(getenv(line + 1), temp);
		else
			temp = ft_create_tmp(line, temp);
		free(line);
	}
	return (temp);
}

void	ft_ctrl_here(int sig)
{
	if (sig == SIGINT)
		exit(1);
}

int	ft_here_doc_open(t_lex *lex, t_global *data, int file, char *cmp)
{
	int		temp;
	char	*line;

	lex = lex->next;
	temp = open("temp", O_CREAT | O_RDWR | O_APPEND, 0644);
	while (1)
	{
		signal(SIGINT, ft_ctrl_here);
		signal(SIGQUIT, SIG_IGN);
		line = readline("> ");
		if (line == NULL)
			break ;
		if (line != NULL)
		{
			if (ft_strcmp(line, cmp) == 0)
				break ;
			if (ft_strlen(line) > 1 && ft_get_env(line + 1, data->envmini))
				temp = ft_create_tmp(ft_get_env(line + 1, data->envmini), temp);
			else
				temp = ft_create_tmp(line, temp);
			free(line);
		}
	}
	file = open("temp", O_RDONLY);
	return (file);
}

int	ft_here_doc_pipe(t_lex *lex, t_global *data)
{
	int	pid;
	int	file;
	int	status;

	pid = fork();
	if (pid == 0)
	{
		if (access("temp", F_OK | W_OK) == 0)
			unlink("temp");
		file = ft_here_doc_open(lex, data, 0, lex->next->content);
		if (file == -1)
			exit(1);
		exit(0);
	}
	signal(SIGINT, SIG_IGN);
	wait(&status);
	signal(SIGINT, ft_controles);
	if (WEXITSTATUS(status) == 1)
		return (-1);
	file = open("temp", O_RDONLY);
	return (file);
}

int	check_here_doc(t_lex *lex, t_global *data)
{
	t_lex	*tmp;

	tmp = lex;
	while (tmp)
	{
		if (tmp->type == 4)
		{
			if (!tmp->next)
			{
				ft_error("", "", \
				"syntax error near unexpected token `newline'", 1);
				return (-1);
			}
			return (ft_here_doc_pipe(tmp, data));
		}
		if (tmp->type == 1)
			break ;
		tmp = tmp->next;
	}
	return (0);
}
