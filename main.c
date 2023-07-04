/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgreiner <rgreiner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 15:02:15 by ogregoir          #+#    #+#             */
/*   Updated: 2023/07/04 18:09:48 by rgreiner         ###   ########.fr       */
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

int		ft_nbr_quotes(char *buf)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while(buf[i])
	{
		if (buf[i] == '"')
			j++;
		i++;
	}
	if (j % 2 != 0)
		{
			printf("Bad arguments");
			exit(1);
		}
	j = j / 2;
	return(j);
}
char	**ft_check_quotes(char *buf)
{
	char	**ret;
	int		nbr_q;
	int		i;
	int		j;
	int		l;

	nbr_q = 0;
	i = 0;
	j = 0;
	l = ft_nbr_quotes(buf);
	if (l == 0)
		return(NULL);
	ret = malloc(sizeof(char*) * (l + 1));
	l = 0;
	while(buf[i])
	{
		if(buf[i] == '"')
			{
				if(i == 0)
				{
				j = i;
				while(buf[i])
				{
				i++;
				if(buf[i] == '"')
					ret[l] = ft_substr(buf, j + 1, i - 1);
				}
				}
				if(ret[l] == NULL)
					ret[l] = ft_substr(buf ,0 ,j);
				l++;
			}
		i++;
	}
	ret[l] = NULL;
	return(ret);
}
static void	check_line(char *rl_line_buffer, char **env, t_data *data, t_lex *lex)
{
	char	**line;
	int	i;
	lex = NULL;
	data = NULL;
	env = NULL;

	i = 0;
	line = ft_check_quotes(rl_line_buffer);
	if(!line)
		line = ft_split(rl_line_buffer, ' ');
	write(2, "PASS\n", 5);
	while(line[i])
		{
			printf("%s\n", line[i]);
			i++;
		}
	lex = ft_lexer(line, lex);
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
	if (ft_strncmp(line[0], "exit", 4) == 0 && ft_strlen(line[0]) == 4)
		ft_exit(line, data);
	if(ft_strncmp(line[0], "$?", 2) == 0 && ft_strlen(line[0]) == 2)
		printf("minishell: %d: command not found\n", data->exit_status);
	//else
	//	ft_not_builtin();
	ft_free_split(line);*/
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
	readline("minishell : ");
	while (rl_line_buffer != NULL)
	{
		check_line(rl_line_buffer, env, &data, &lex);
		//ft_variables_env(rl_line_buffer);
		add_history(rl_line_buffer);
		readline("minishell : ");
	}
	return (0);
}
