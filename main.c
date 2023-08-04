/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 15:02:15 by ogregoir          #+#    #+#             */
/*   Updated: 2023/08/04 13:36:04 by marvin           ###   ########.fr       */
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
	char	**str;

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
		ft_env(line, env, data);
	*/if (ft_strncmp(str[0], "exit", 4) == 0 && ft_strlen(str[0]) == 4)
		ft_exit(str, data);
	if(ft_strncmp(str[0], "$?", 2) == 0 && ft_strlen(str[0]) == 2)
		printf("minishell: %d: command not found\n", data->exit_status);
	ft_not_builtin(lex, data, env);
	//ft_free_split(line);
	return ;
}

int	main(int argc, char **argv, char **env)
{	
	t_data data;
	t_lex lex;
	char	*input;

	(void)argc;
	(void)argv;
	data.exit_status = 0;
	
	if (!env[0])
		exit(1);
	non_canonique();
	signal(SIGINT, ft_controles);
    signal(SIGQUIT, ft_controles);
	input = readline("minishell: ");
	while (rl_line_buffer != NULL)
	{	
		if (input == NULL)
			exit(0);
		check_line(rl_line_buffer, env, &data, &lex);
		input = readline("minishell: ");
		//ft_variables_env(rl_line_buffer);
		add_history(rl_line_buffer);
		free (input);
	}
	return (0);
}
