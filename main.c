/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgreiner <rgreiner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 15:02:15 by ogregoir          #+#    #+#             */
/*   Updated: 2023/10/24 16:30:39 by rgreiner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_lexer(t_lex *lex)
{
	t_lex *tmp;

	tmp = lex;
	while (tmp)
	{
		printf("-------------------\n");
		printf("%s\n", tmp->content);
		printf("%u\n", tmp->type);
		printf("-------------------\n");
		tmp = tmp->next;
	}
}

static void check_line(t_global *data, char *rl_line_buffer, t_lex *lex)
{
	char	**str;
	int		l;
	
	lex = NULL;
	l = 0;
	if (l == 1)
		return;
	if (ft_detect_quotes(rl_line_buffer) == 1)
	{
		lex = ft_quote(rl_line_buffer, lex, data);
		if (lex->next)
			lex = ft_join(lex, data);
	}
	else
		str = ft_split(rl_line_buffer, ' ');
	if (!lex)
		lex = ft_lexer(str, lex, data);
	lex = dollar_lexer(lex, data);
	//print_lexer(lex);
	if(!lex)
		return;
	if (ft_strncmp(lex->content, "exit", 4) == 0 && ft_strlen(lex->content) == 4)
		ft_exit(lex, data);
	if(ft_strncmp(lex->content, "cd", 2) == 0 && ft_strlen(lex->content) == 2)
			{
				data->error_code = ft_cd(data, lex);
				return ;
			}
	if (ft_verif_exp(rl_line_buffer, lex) == 2)
		lex = lex->next;
	if (ft_verif_exp(rl_line_buffer, lex) == 0 && !lex->next)
	{
		data->error_code= ft_export3(data, rl_line_buffer); 
		return;
	}
	if (rl_line_buffer[0] == '\0')
		return;
	if(lex->next && lex->type == 1)
		lex = lex->next; 
	if (rl_line_buffer[0] == '\0')
		return;
	ft_not_builtin(lex, data);
	return;
}

int main(int argc, char **argv, char **env)
{
	t_lex lex;
	t_global *data;
	char *input;

	(void)argc;
	(void)argv;

	if (!env[0])
		exit(1);
	data = malloc(sizeof(t_global));
	non_canonique();
	signal(SIGQUIT, ft_controles);
	ft_init_token(data);
	data->envmini = create_env(env, data);
	data->env_exp = create_env(env, data);
	input = readline("minishell: ");
	// ft_print_tok(data);
	while (rl_line_buffer != NULL)
	{
		add_history(rl_line_buffer);
		signal(SIGINT, ft_controles);
		if (ft_strncmp("cat", rl_line_buffer, ft_strlen(rl_line_buffer)) == 0)
			signal(SIGINT, ft_ctrlb);
		free(input);
		if (input == NULL)
			exit(data->error_code);
		check_line(data, rl_line_buffer, &lex);
		input = readline("minishell: ");
		// ft_variables_env(rl_line_buffer);
	}
	return (data->error_code);
}