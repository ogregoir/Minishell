/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgreiner <rgreiner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 16:39:22 by marvin            #+#    #+#             */
/*   Updated: 2023/10/15 14:20:32 by rgreiner         ###   ########.fr       */
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
	if(lex->next->next && lex->next->type == 8 && lex->next->next->type == 8)
		{
			ft_putendl_fd("minishell: exit: too many arguments", 2);
			data->error_code = 1;
			exit(1);
		}
	if (ft_check_nbr(lex->next->content) == 1 && lex->next->content[0] != '+' && lex->next->content[0] != '-' \
	&& lex->next->type == 8 && lex->next->next->type == 8)
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

int		ft_pwd(int file)
{
	char	*buf;

	buf = NULL;
	buf = getcwd(buf, 100);
	if(file != 1)
		dup2(file, STDOUT_FILENO);
	ft_putendl_fd(buf, file);
	free(buf);
	return(0);
}

int	ft_env(t_lex *lex, t_global *data, int file)
{
	int	i;

	i = 0;
	if(file != 1)
		dup2(file, STDOUT_FILENO);
	if (lex->next != NULL && lex->next->type != 1 && lex->next->type != 3 && lex->next->type != 5)
	{
		printf("env: %s: No such file or directory\n", lex->next->content);
		return (127);
	}
	while (data->envmini[i] != NULL)
	{
		ft_putendl_fd(data->envmini[i], file);
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

int		ft_echo(t_lex *lex , int file)
{
	int nl;

	nl = 0;
	if (!lex->next)
	{
		printf("\n");
		return(0) ;
	}
	if(ft_search_token(lex) == 1 && ft_multi_redi(lex) == 1)
		exit(0);
	lex = lex->next;
	nl = ft_echo_nl(&lex);
	if (!lex)
		return (0);
	if(file != 1)
		dup2(file, STDOUT_FILENO);
	while(lex)
	{
		if(lex->next && lex->next->next && (lex->type == 3 || lex->type == 5))
			lex = lex->next->next;
		if(lex->type == 8)
			{
				ft_putstr_fd(lex->content, file);
				if(lex->next && lex->next->type == 8)
					ft_putstr_fd(" ", file);
			}
		if(!lex->next)
			break;
		lex = lex->next;
		if(lex->type == 3 || lex->type == 5 || lex->type == 1)
			break;
	}
	if(nl == 0)
		ft_putendl_fd("", file);
	return (0);
}