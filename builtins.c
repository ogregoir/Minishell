/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgreiner <rgreiner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 14:17:58 by rgreiner          #+#    #+#             */
/*   Updated: 2023/08/31 10:41:13 by rgreiner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_lex *lex)
{
	printf("exit\n");
	if (lex->next == NULL)
		exit (error_code);
	if (ft_check_nbr(lex->next->content) == 1)
	{
		printf("minishell: exit: %s numeric argument required\n", lex->next->content);
		exit (EXIT_FAILURE);
	}
	else
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

int	ft_env(t_lex *lex, char **env)
{
	int	i;

	i = 0;
	if (lex->next != NULL)
	{
		printf("env: %s: No such file or directory\n", lex->next->content);
		return(127) ;
	}
	while (env[i] != NULL)
	{
		printf("%s\n", env[i]);
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