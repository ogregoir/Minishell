/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgreiner <rgreiner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 15:02:15 by ogregoir          #+#    #+#             */
/*   Updated: 2023/10/05 11:04:47 by rgreiner         ###   ########.fr       */
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

t_lex *ft_join(t_lex *lex)
{
	t_lex *tmp;
	char *str;

	tmp = NULL;
	while(lex->next)
	{
		while(lex->next && ft_strncmp(lex->content, " ", 1) == 0 && ft_strlen(lex->content) == 1 && lex->type != 0)
			lex = lex->next;
		if (ft_strncmp(lex->content, " ", 1) != 0 || ft_strlen(lex->content) != 1)
			{
				if (lex->next && ft_strncmp(lex->next->content, " ", 1) == 0 && ft_strlen(lex->next->content) == 1)
					{
					if (!tmp)
						tmp = ft_lstnew(lex->content, lex->type);
					else
						addcontent(tmp, lex->content, lex->type);
					}
				else if(lex->next)
					{
					str = ft_strjoin(lex->content, lex->next->content);
					if (!tmp)
						tmp = ft_lstnew(str, lex->type);
					else
						addcontent(tmp, str, lex->type);
					lex = lex ->next;
					}
				while(lex->next && ft_strncmp(lex->content, " ", 1) == 0 && ft_strlen(lex->content) == 1 && lex->type != 0)
					lex = lex->next;
			}
			else if (!tmp && (ft_strncmp(lex->content, " ", 1) != 0 || ft_strlen(lex->content) != 1))
				tmp = ft_lstnew(lex->content, lex->type);
			else if (ft_strncmp(lex->content, " ", 1) != 0 || ft_strlen(lex->content) != 1)
				addcontent(tmp, lex->content, lex->type);
			if(lex->next)
				lex = lex->next;
	}
	if(ft_strncmp(lex->content, " ", 1) == 0 && ft_strlen(lex->content) == 1)
		return(tmp);
	if (!tmp && ft_strncmp(ft_last_ele(tmp), str, ft_strlen(str) != 0))
		tmp = ft_lstnew(lex->content, lex->type);
	else if(ft_strncmp(ft_last_ele(tmp), str, ft_strlen(str) != 0))
		addcontent(tmp, lex->content, lex->type);
	return(tmp);
}

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

t_lex	*ft_builtin_exec(t_global *data, t_lex *lex, char **str)
{
	int file;
	int old;
	
	file = 1;
	file = ft_builtin_redi(lex, file);
	old = dup(STDOUT_FILENO);
	if (ft_strncmp(lex->content, "exit", 4) == 0 && ft_strlen(lex->content) == 4)
		ft_exit(lex);
	else if (ft_strncmp(lex->content, "echo", 4) == 0 && ft_strlen(lex->content) == 4)
		data->error_code = ft_echo(lex, file);
	else if(ft_strncmp(lex->content, "cd", 2) == 0 && ft_strlen(lex->content) == 2)
		data->error_code = ft_cd(data, str);
	else if (ft_strncmp(lex->content, "pwd", 3) == 0 && ft_strlen(lex->content) == 3)
		data->error_code = ft_pwd(file);
	else if(ft_strncmp(lex->content, "export", 6) == 0)
		data->error_code = ft_export(str, data);
	else if(ft_strncmp(lex->content, "unset", 5) == 0)
		data->error_code = ft_unset(str, data);
	else if (ft_strncmp(lex->content, "env", 3) == 0 && ft_strlen(lex->content) == 3)
		error_code = ft_env(lex, env, file);
	else if (lex->type == 0)
		error_code = ft_dollar_env(lex, env);
	close_redi(old, file);
	return (lex);
}

static void	check_line(t_global *data, char *rl_line_buffer, t_lex *lex)
{
	char	**str;
	
	lex = NULL;
	if (ft_detect_quotes(rl_line_buffer) == 1)
		{
			lex = ft_quote(rl_line_buffer, lex);
			if(lex->next)
				lex = ft_join(lex);
		}
	else
		str = ft_split(rl_line_buffer, ' ');
	if(!lex)
		lex = ft_lexer(str, lex);
	//print_lexer(lex);
	if (rl_line_buffer[0] == '\0')
		return;
	while(lex)
	{
	if(lex->next && lex->type == 1)
		lex = lex->next;
	if(ft_builtin(lex->content, lex->type) == 0)
		{
		ft_builtin_exec(lex, str, env);
		while(lex && lex->type != 1)
			lex = lex->next;
		}
	else
		{
		ft_not_builtin(lex, env);
		while(lex && ft_builtin(lex->content, lex->type) != 0)
			lex = lex->next;
		}
	}
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
	ft_free_oldpwd(envmini);
	return(envmini);
}

int	main(int argc, char **argv, char **env)
{	
	t_lex lex;
	t_global	*data;
	char	*input;
	//char	**envmini;
	
	(void)argc;
	(void)argv;

	if (!env[0])
		exit(1);
	data = malloc(sizeof(t_global));
	non_canonique();
	signal(SIGINT, ft_controles);
	signal(SIGQUIT, ft_controles);
	data->envmini = create_env(env);
	input = readline("minishell: ");
	ft_init_token(data);
	//ft_print_tok(data);
	while (rl_line_buffer != NULL)
	{	
		add_history(rl_line_buffer);
		free (input);
		if (input == NULL)
			exit(data->error_code);
		check_line(data, rl_line_buffer, &lex);
		input = readline("minishell: ");
		//ft_variables_env(rl_line_buffer);
	}
	return(error_code);
	return(error_code);
}