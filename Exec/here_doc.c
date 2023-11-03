/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgreiner <rgreiner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 09:37:09 by rgreiner          #+#    #+#             */
/*   Updated: 2023/11/03 23:20:58 by rgreiner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static volatile sig_atomic_t keep = 1;

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned int	s;

	s = 0;
	while (s1[s] != '\0' && s2[s] != '\0' && s1[s] == s2[s])
		s++;
	return (*(unsigned char *)(s1 + s) - *(unsigned char *)(s2 + s));
}

int	ft_create_tmp(char *line, int temp)
{
	int	i;

	i = 0;
	line = ft_strjoin(line, "\n");
	while (line[i])
	{
		write(temp, &line[i], 1);
		i++;
	}
	return (temp);
}

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
	{
	//	rl_on_new_line();
	//	rl_replace_line("", 0);
		exit(1);
	}
}


int ft_here_doc_open(t_lex *lex, t_global *data)
{
	int		temp;
    int     file;
	char	*line;
	char	*cmp;
	
	keep = 1;
    lex = lex->next;
	cmp = lex->content;
	if(access("temp", F_OK | W_OK) == 0)
		unlink("temp");
	temp = open("temp", O_CREAT | O_RDWR | O_APPEND, 0644);
	while (1)
	{	
		signal(SIGINT, ft_ctrl_here);
		signal(SIGQUIT, SIG_IGN);
		line = readline("> ");
		if(line == NULL)
			break;
		if (line != NULL)
		{
		if (ft_strcmp(line, cmp) == 0)
			break ;	
		if(ft_strlen(line) > 1 && ft_get_env(line + 1, data->envmini) != NULL)
			temp = ft_create_tmp(ft_get_env(line + 1, data->envmini), temp);
		else
			temp = ft_create_tmp(line, temp);
		free(line);
		}
	}
	file = open("temp", O_RDONLY);

    return(file);
}

int	ft_here_doc_pipe(t_lex *lex, t_global *data)
{
	int	pid;
	int file;
	int status;

	pid = fork();
	if (pid == 0)
		{
			file = ft_here_doc_open(lex, data);
			if(file == -1)
				exit(1);
			exit(0);
		}
	signal(SIGINT, SIG_IGN);
	wait(&status);
	signal(SIGINT, ft_controles);
	if(WEXITSTATUS(status) == 1)
		return (-1);
	file = open("temp", O_RDONLY);	
	return (file);
}


int	check_here_doc(t_lex *lex, t_global *data)
{
	t_lex *tmp;

	tmp = lex;
	while(tmp)
	{
		if(tmp->type == 4)
		{
			if(!tmp->next)
			{
			ft_error("","", "syntax error near unexpected token `newline'", 1);
			return (-1);
			}
			return(ft_here_doc_pipe(tmp, data));
		}
		if(tmp->type == 1)
			break;
		tmp = tmp->next;
	}
	return (0);
}