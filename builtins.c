/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 16:39:22 by marvin            #+#    #+#             */
/*   Updated: 2023/10/02 23:39:40 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_lex *lex, t_global *data)
{
	int i;

	i = 0;
	printf("exit\n");
	if (lex->next == NULL)
		exit (data->error_code);
	if(lex->next->next)
		{
			ft_putendl_fd("minishell: exit: too many arguments", 2);
			data->error_code = 1;
			exit(1);
		}
	if (ft_check_nbr(lex->next->content) == 1 && lex->next->content[0] != '+' && lex->next->content[0] != '-')
	{
		ft_putendl_fd(" numeric argument required", 2);
		data->error_code = 2;
		exit (2);
	}
	if(lex->next->content[0] == '-')
		{
			i = ft_atoi(lex->next->content);
			i = 256 + i;
			exit(i);
		}
	exit (ft_atoi(lex->next->content));
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

int	ft_env(t_lex *lex, t_global *data)
{
	int	i;

	i = 0;
	if (lex->next != NULL)
	{
		printf("env: %s: No such file or directory\n", lex->next->content);
		return (127);
	}
	while (data->envmini[i] != NULL)
	{
		printf("%s\n", data->envmini[i]);
		i++;
	}
	return(0);
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

int		ft_search_token(t_lex *lex)
{
	t_lex *tmp;

	tmp = lex;
	while(tmp)
	{
		if(tmp->type == 1)
			return (1);
		tmp = tmp->next;
	}
	return (0);
	
}
int		ft_echo(t_lex *lex, t_global *data)
{
	int nl;

	nl = 0;
	if(ft_search_token(lex) > 0)
		return (0);
	if (!lex->next)
	{
		printf("\n");
		return(0) ;
	}
	lex = lex->next;
	nl = ft_echo_nl(&lex);
	if (!lex)
		return(0) ;
	while(lex)
	{
		if(lex->next && lex->next->next && lex->type == 2)
			lex = lex->next->next;
		if(lex->type == 8)
			printf("%s",lex->content);
		if(lex && lex->type == 0)
		{
		if(ft_strlen(lex->content) > 1 || ft_strncmp(lex->content, "?", 1) == 0)
			{
			if(ft_strncmp(lex->content, "?", 1) == 0 && ft_strlen(lex->content) >= 1)
				{
				if(lex->content[2])
					printf("%d%s\n", data->error_code, lex->content + 1);
				else
					printf("%d\n", data->error_code);
				}
				else
					printf("%s\n", getenv(lex->content));
				return (0);
			}
		else
			printf("$");
		}
		if(lex->next)
			printf(" ");
		lex = lex->next;
	}
	if(nl == 0)
		printf("\n");
	return (0);
}