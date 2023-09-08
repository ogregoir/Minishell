/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgreiner <rgreiner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 15:02:15 by ogregoir          #+#    #+#             */
/*   Updated: 2023/09/08 09:52:45 by rgreiner         ###   ########.fr       */
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
		if (str[i][0] == '\0')
			{
				j++;
				ret[j] = ft_strdup(str[i]);
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

static void	check_line(char *rl_line_buffer, char **env, t_lex *lex, t_cd	*path)
{
	char	**str;
	char	*buf;

	buf = NULL;
	if (ft_detect_quotes(rl_line_buffer) == 1)
	{
		str = ft_quote(rl_line_buffer);
		if(str[1] != NULL)
			str = ft_join(str);
	}
	else
		str = ft_split(rl_line_buffer, ' ');
	lex = ft_lexer(str, lex);
	print_lexer(lex);
	buf = getcwd(buf, 100);
	if (rl_line_buffer[0] == '\0')
		return;
	if (ft_strncmp(lex->content, "exit", 4) == 0 && ft_strlen(lex->content) == 4)
		ft_exit(lex);
	else if (ft_strncmp(lex->content, "echo", 4) == 0 && ft_strlen(lex->content) == 4)
		error_code = ft_echo(lex);
	else if(ft_strncmp(lex->content, "cd", 2) == 0 && ft_strlen(lex->content) == 2)
		ft_cd(str, buf, path);
	else if (ft_strncmp(lex->content, "pwd", 3) == 0 && ft_strlen(lex->content) == 3)
		error_code = ft_pwd();
	else if(ft_strncmp(lex->content, "export", 6) == 0)
		ft_export(str, env);
	else if(ft_strncmp(lex->content, "unset", 5) == 0)
		ft_unset(str, env);
	else if (ft_strncmp(lex->content, "env", 3) == 0 && ft_strlen(lex->content) == 3)
		error_code = ft_env(lex, env);
	else if (ft_strncmp(lex->content, "$", 1) == 0 && ft_strlen(lex->content) == 1)
			ft_dollar(lex);
	else
		ft_not_builtin(lex, env);
	return ;
}


int	main(int argc, char **argv, char **env)
{	
	t_lex lex;
	char	*input;
	t_cd	*path;
	
	(void)argc;
	(void)argv;

	path = malloc(sizeof(t_cd));
	if (!env[0])
		exit(1);
	non_canonique();
	signal(SIGINT, ft_controles);
	signal(SIGQUIT, ft_controles);
	input = readline("minishell: ");
	while (rl_line_buffer != NULL)
	{	
		add_history(rl_line_buffer);
		free (input);
		if (input == NULL)
			exit(0);
		check_line(rl_line_buffer, env, &lex, path);
		input = readline("minishell: ");
		//ft_variables_env(rl_line_buffer);
	}
	return (0);
}