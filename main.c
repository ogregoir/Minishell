/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgreiner <rgreiner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 15:02:15 by ogregoir          #+#    #+#             */
/*   Updated: 2023/09/25 11:35:42 by rgreiner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int error_code = 0;

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

int	ft_nbr_space(char **str)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while(str[i])
		{
			if(str[i][0] == '\0')
				j++;
			i++;
		}
		return(j);
}

char **ft_join(char **str)
{
	int i;
	int j;
	char **ret;

	i = 1;
	j = 0;

	ret = malloc(sizeof(char *) * (ft_nbr_space(str) + 1));
	ret[0] = ft_strdup(str[0]);
	while(str[i])
	{
		if (str[i][0] == 32)
			{
				j++;
				ret[j] = ft_strdup2(str[i], 1);
			}
		else
			ret[j] = ft_strjoin_free(ret[j], str[i]);
		i++;
	}
	j++;
	ret[j] = NULL;
	free(str);
	return(ret);
}

static void	check_line(char *rl_line_buffer, char **env, t_lex *lex)
{
	char	**str;

	if (ft_detect_quotes(rl_line_buffer) == 1)
	{
		str = ft_quote(rl_line_buffer);
		if(str[1] != NULL)
			str = ft_join(str);
	}
	else
		str = ft_split(rl_line_buffer, ' ');
	lex = ft_lexer(str, lex);
	//print_lexer(lex);
	if (rl_line_buffer[0] == '\0')
		return;
	if (ft_strncmp(lex->content, "exit", 4) == 0 && ft_strlen(lex->content) == 4)
		ft_exit(lex);
	else if (ft_strncmp(lex->content, "echo", 4) == 0 && ft_strlen(lex->content) == 4)
		error_code = ft_echo(lex, env);
	else if(ft_strncmp(lex->content, "cd", 2) == 0 && ft_strlen(lex->content) == 2)
		error_code = ft_cd(env, str);
	else if (ft_strncmp(lex->content, "pwd", 3) == 0 && ft_strlen(lex->content) == 3)
		error_code = ft_pwd();
	else if(ft_strncmp(lex->content, "export", 6) == 0)
		error_code = ft_export(str, env);
	else if(ft_strncmp(lex->content, "unset", 5) == 0)
		error_code= ft_unset(str, env);
	else if (ft_strncmp(lex->content, "env", 3) == 0 && ft_strlen(lex->content) == 3)
		error_code = ft_env(lex, env);
	else if (ft_strncmp(lex->content, "$", 1) == 0 && ft_strlen(lex->content) == 1)
	{
		if (ft_strncmp(lex->next->content, "?", 1) == 0)
			ft_dollar(lex);
		else
			error_code = ft_dollar_env(lex, env);
	}
			
	else
		ft_not_builtin(lex, env);
	return ;
}

char **create_env(char **env)
{
	char **envmini;
	int	i;

	i = 0;
	while(env[i])
		i++;
	envmini = malloc(sizeof(char**) * i + 1);
	i = 0;	
	while(env[i])
	{
		envmini[i] = ft_strdup(env[i]);
		i++;
	}
	return(envmini);
}

int	main(int argc, char **argv, char **env)
{	
	t_lex lex;
	char	*input;
	char **envmini;
	
	(void)argc;
	(void)argv;

	if (!env[0])
		exit(1);
	non_canonique();
	signal(SIGINT, ft_controles);
	signal(SIGQUIT, ft_controles);
	envmini = create_env(env);
	input = readline("minishell: ");
	ft_free_oldpwd(envmini);
	while (rl_line_buffer != NULL)
	{	
		add_history(rl_line_buffer);
		free (input);
		if (input == NULL)
			exit(0);
		check_line(rl_line_buffer, envmini, &lex);
		input = readline("minishell: ");
		//ft_variables_env(rl_line_buffer);
	}
	return (0);
}