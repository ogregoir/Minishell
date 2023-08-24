/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogregoir <ogregoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 14:17:58 by rgreiner          #+#    #+#             */
/*   Updated: 2023/07/03 20:03:05 by ogregoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(char **line, t_data *data)
{
	printf("exit\n");
	if (line[1] == NULL)
		exit (data->exit_status);
	if (ft_check_nbr(line) == 1)
	{
		printf("minishell: exit: %s numeric argument required\n", line[1]);
		exit (EXIT_FAILURE);
	}
	else
		exit (ft_atoi(line[1]));
}

int		ft_pwd(void)
{
	char	*buf;

	buf = NULL;
	buf = getcwd(buf, 100);
	printf("%s\n", buf);
	free(buf);
	return(0);
}

void	ft_env(char **line, char **env, t_data *data)
{
	int	i;

	i = 0;
	if (line[1] != NULL)
	{
		printf("env: %s: No such file or directory\n", line[1]);
		data->exit_status = 127;
		return ;
	}
	while (env[i] != NULL)
	{
		printf("%s\n", env[i]);
		i++;
	}
	data->exit_status = 0;
}

int	ft_echo_nl(t_lex **lex)
{
	int i;

	if(ft_strncmp((*lex)->content, "-n", 2) != 0)
			return (0);
	while(*lex)
	{	
		i = 1;
		if(ft_strncmp((*lex)->content, "-n", 2) != 0)
			break;
		while((*lex)->content[i])
		{
			if((*lex)->content[i] != 'n')
				return (0);
			i++;
		}
		if(i != 1)
			(*lex) = (*lex)->next;
	}
	return (1);
}

int		ft_echo(t_lex *lex)
{
	int nl;

	nl = 0;
	if (!lex->next)
	{
		printf("\n");
		return(0) ;
	}
	lex = lex->next;
	nl = ft_echo_nl(&lex);
	if (!lex)
		return(0) ;
	while(lex && lex->type == 8)
	{
		printf("%s",lex->content);
		if(lex->next)
			printf(" ");
		lex = lex->next;
	}
	if(nl == 0)
		printf("\n");
	return (0);
}