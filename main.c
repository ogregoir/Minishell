/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogregoir <ogregoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 15:02:15 by ogregoir          #+#    #+#             */
/*   Updated: 2023/07/10 15:33:05 by ogregoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_lexer(t_lex *lex)
{
	t_lex	*tmp;
	
	tmp = lex;
	while(tmp)
	{
		printf("-------------------\n");
		printf("%s\n", tmp->content);
		printf("%u\n", tmp->type);
		printf("-------------------\n");
		tmp = tmp -> next;
	}
}

static void	check_line(char *rl_line_buffer, char **env, t_data *data, t_lex *lex)
{
	char	**line;
	char	**str;
	int	i;

	i = 0;
	line = ft_split(rl_line_buffer, ' ');
	str = ft_quote(rl_line_buffer);
	lex = ft_lexer(str, lex);
	print_lexer(lex);
	/*
	if (ft_strncmp(line[0], "echo", 4) == 0 && ft_strlen(line[0]) == 4)
		ft_echo(line, 0, data);
	//else if(ft_strncmp(line, "cd", 2) == 0)
	//	ft_cd();
	if (ft_strncmp(line[0], "pwd", 3) == 0 && ft_strlen(line[0]) == 3)
		ft_pwd(data);
	else if(ft_strncmp(line, "export", 6) == 0)
		ft_export();
	else if(ft_strncmp(line, "unset", 5) == 0)
		ft_unset();
	if (ft_strncmp(line[0], "env", 3) == 0 && ft_strlen(line[0]) == 3)
		ft_env(line, env, data);*/
	if (ft_strncmp(line[0], "exit", 4) == 0 && ft_strlen(line[0]) == 4)
		ft_exit(line, data);
	if(ft_strncmp(line[0], "$?", 2) == 0 && ft_strlen(line[0]) == 2)
		printf("minishell: %d: command not found\n", data->exit_status);
	ft_not_builtin(lex, data, env);
	ft_free_split(line);
	return ;
}

int	main(int argc, char **argv, char **env)
{	
	t_data data;
	t_lex lex;

	argc = 0;
	argv = NULL;
	data.exit_status = 0;
	if (!env[0])
		exit(1);
	readline("minishell: ");
	while (rl_line_buffer != NULL)
	{
		check_line(rl_line_buffer, env, &data, &lex);
		//ft_variables_env(rl_line_buffer);
		add_history(rl_line_buffer);
		readline("minishell: ");
	}
	return (0);
}
