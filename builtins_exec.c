/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgreiner <rgreiner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 16:32:41 by rgreiner          #+#    #+#             */
/*   Updated: 2023/10/17 16:58:28 by rgreiner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int	ft_builtin(char *content, int type)
{
	if (ft_strncmp(content, "exit", 4) == 0 && ft_strlen(content) == 4)
		return (0);
	if (ft_strncmp(content, "echo", 4) == 0 && ft_strlen(content) == 4)
		return (0);
	if(ft_strncmp(content, "cd", 2) == 0 && ft_strlen(content) == 2)
		return (0);
	if (ft_strncmp(content, "pwd", 3) == 0 && ft_strlen(content) == 3)
		return (0);
	if(ft_strncmp(content, "export", 6) == 0)
		return (0);
	if(ft_strncmp(content, "unset", 5) == 0)
		return (0);
	if (ft_strncmp(content, "env", 3) == 0 && ft_strlen(content) == 3)
		return (0);
	if (type == 0)
		return (0);
	return (1);
}
void	exec_builtin_pipe(int file, t_global *data, t_lex *lex, char **str)
{
	if (ft_strncmp(lex->content, "echo", 4) == 0 && ft_strlen(lex->content) == 4)
		data->error_code = ft_echo(lex, file);
	else if(ft_strncmp(lex->content, "cd", 2) == 0 && ft_strlen(lex->content) == 2)
			data->error_code = ft_cd(data, str);
	else if (ft_strncmp(lex->content, "pwd", 3) == 0 && ft_strlen(lex->content) == 3)
		data->error_code = ft_pwd(file);
	else if(ft_strncmp(lex->content, "export", 6) == 0)
		data->error_code = ft_export(lex, data);
	else if(ft_strncmp(lex->content, "unset", 5) == 0)
		data->error_code = ft_unset(str, data);
	else if (ft_strncmp(lex->content, "env", 3) == 0 && ft_strlen(lex->content) == 3)
		error_code = ft_env(lex, data, file);
	else if (lex->type == 0)
		error_code = ft_dollar_env(lex, data);
}

void    ft_exec_main(int file, t_lex *lex, t_global *data, char **str)
{
	if (ft_strncmp(lex->content, "echo", 4) == 0 && ft_strlen(lex->content) == 4)
		data->error_code = ft_echo(lex, file);
	else if(ft_strncmp(lex->content, "cd", 2) == 0 && ft_strlen(lex->content) == 2)
			data->error_code = ft_cd(data, str);
	else if (ft_strncmp(lex->content, "pwd", 3) == 0 && ft_strlen(lex->content) == 3)
		data->error_code = ft_pwd(file);
	else if(ft_strncmp(lex->content, "export", 6) == 0)
		data->error_code = ft_export(lex, data);
	else if(ft_strncmp(lex->content, "unset", 5) == 0)
		data->error_code = ft_unset(str, data);
	else if (ft_strncmp(lex->content, "env", 3) == 0 && ft_strlen(lex->content) == 3)
		error_code = ft_env(lex, data, file);
	else if (lex->type == 0)
		error_code = ft_dollar_env(lex, data);
}

t_lex	*ft_builtin_exec(t_global *data, t_lex *lex, char **str)
{
	int file;
	int old;
	int status;
	pid_t	pid;

	
	file = 1;
	if (ft_strncmp(lex->content, "exit", 4) == 0 && ft_strlen(lex->content) == 4)
		ft_exit(lex, data);
	if(ft_search_token(lex) == 1)
	{
		pid = fork();
		if(pid == 0)
		{
		file = ft_builtin_redi(lex, file, 1);
		old = dup(STDOUT_FILENO);
		if(ft_multi_redi(lex) == 0)
			exec_builtin_pipe(file, data, lex, str);
		close_redi(old, file);
		exit(0);
		}
		while (wait(&status) > 0)
			;
		data->error_code = WEXITSTATUS(status);
	}
	else
	{
    file = ft_builtin_redi(lex, file, 0);
	old = dup(STDOUT_FILENO);
    ft_exec_main(file, lex, data, str);
	close_redi(old, file);
	}
	return (lex);
}