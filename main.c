/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgreiner <rgreiner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 15:02:15 by ogregoir          #+#    #+#             */
/*   Updated: 2023/11/16 12:37:43 by rgreiner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_builtins(t_global *data, t_lex *lex)
{
	if (ft_strncmp(lex->content, "exit", 4) == 0 && \
		ft_strlen(lex->content) == 4)
	{
		ft_exit(lex, data);
		return (0);
	}
	if (ft_strncmp(lex->content, "cd", 2) == 0 && \
		ft_strlen(lex->content) == 2)
	{
		data->error_code = ft_cd(data, lex);
		return (0);
	}
	if (ft_strncmp(lex->content, "unset", 5) == 0 && \
		ft_strlen(lex->content) == 5)
	{
		data->error_code = ft_unset(lex, data);
		return (0);
	}
	if (ft_strncmp(lex->content, "export", 6) == 0 && \
		ft_strlen(lex->content) == 6)
	{
		data->error_code = ft_export(lex, data);
		return (0);
	}
	return (1);
}

t_lex	*create_lex(t_lex *lex, t_global *data, char **str)
{
	if (rl_line_buffer[0] == '\0')
		return (lex);
	if (ft_detect_quotes(rl_line_buffer, 0, 0, 0) == 1)
	{
		lex = ft_quote(rl_line_buffer, lex, data, 0);
		if (lex->next)
			lex = ft_join(lex, data);
	}
	else
		str = ft_split(rl_line_buffer, ' ');
	if (!lex)
		lex = ft_lexer(str, lex, data);
	lex = dollar_lexer(lex, data);
	if (str)
		free(str);
	return (lex);
}

static void	check_line(t_global *data, t_lex *lex, char **str)
{
	lex = create_lex(lex, data, str);
	if (!lex || check_err(lex) == 1)
	{
		ft_free_split(str);
		return ;
	}
	if (ft_check_builtins(data, lex) == 0)
	{
		if (str)
			ft_free_split(str);
		ft_free_list(lex);
		return ;
	}
	if (ft_export3(lex, data) == 0)
	{
		ft_free_list(lex);
		ft_free_split(str);
		return ;
	}
	lex = record_exp(lex);
	data->error_code = ft_exec(lex, data);
	if (str)
		ft_free_split(str);
	ft_free_list(lex);
	return ;
}

void	shell(char *input, t_global *data, t_lex *lex)
{
	input = readline("minishell: ");
	while (rl_line_buffer != NULL)
	{
		add_history(rl_line_buffer);
		if (ft_strncmp("cat", rl_line_buffer, ft_strlen(rl_line_buffer)) == 0)
			signal(SIGINT, ft_ctrlb);
		free(input);
		if (input == NULL)
		{
			ft_free_global(data);
			exit(data->error_code);
		}
		check_line(data, lex, NULL);
		input = readline("minishell: ");
	}
	ft_free_char(data);
}

int	main(int argc, char **argv, char **env)
{
	t_lex		*lex;
	t_global	*data;
	char		*input;

	(void)argc;
	(void)argv;
	if (!env[0])
		exit(1);
	lex = NULL;
	input = NULL;
	non_canonique();
	data = malloc(sizeof(t_global));
	signal(SIGQUIT, ft_controles);
	signal(SIGINT, ft_controles);
	ft_init_token(data, env);
	shell(input, data, lex);
	return (data->error_code);
}
