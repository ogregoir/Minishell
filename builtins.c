/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgreiner <rgreiner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 16:39:22 by marvin            #+#    #+#             */
/*   Updated: 2023/10/05 14:03:16 by rgreiner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_redi(int out, int file)
{
	if(file != 1)
	{
		dup2(out, STDOUT_FILENO);
		close(file);
		close(out);
	}
}

void	ft_exit(t_lex *lex)
{
	int i;

	i = 0;
	printf("exit\n");
	if (lex->next == NULL)
		exit (error_code);
	if(lex->next->next && lex->next->type == 8 && lex->next->next->type == 8)
		{
			ft_putendl_fd("minishell: exit: too many arguments", 2);
			error_code = 1;
			exit(1);
		}
	if (ft_check_nbr(lex->next->content) == 1 && lex->next->content[0] != '+' && lex->next->content[0] != '-' \
	&& lex->next->type == 8 && lex->next->next->type == 8)
	{
		ft_putendl_fd(" numeric argument required", 2);
		error_code = 2;
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

int	ft_env(t_lex *lex, char **env, int file)
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
	while (env[i] != NULL)
	{
		ft_putendl_fd(env[i], file);
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
int		ft_multi_redi(t_lex *tmp)
{
	t_lex *tmp2;
	
	tmp2 = tmp;
	tmp2 = tmp2->next;
	while(tmp2)
	{
		if(tmp2->type == 3 || tmp2->type == 5)
			return(0);
		tmp2 = tmp2->next;
	}
	return(1);
}

int		ft_builtin_redi(t_lex *lex, int file)
{
	t_lex *tmp;
	tmp = lex;
	
	while(tmp)
	{
		if(tmp->next && tmp->type == 3)
		{
			file = openfile(tmp->next->content, 1);
			if(ft_multi_redi(tmp) == 1)
				return(file);
			close(file);
		}
		if(tmp->next && tmp->type == 5)
		{	
			file = openfile(tmp->next->content, 0);
			if(ft_multi_redi(tmp) == 1)
				return(file);
			close(file);
		}
		tmp = tmp->next;
	}
	return(1);
}

int		ft_echo(t_lex *lex , int file, t_global *data)
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
		return (0);
	if(file != 1)
		dup2(file, STDOUT_FILENO);
	while(lex)
	{
		if(lex->next && lex->next->next && lex->type == 2)
			lex = lex->next->next;
		if(lex->type == 8)
			ft_putstr_fd(lex->content, file);
		if(lex && lex->type == 0)
		{
		if(ft_strlen(lex->content) > 1 || ft_strncmp(lex->content, "?", 1) == 0)
			{
			if(ft_strncmp(lex->content, "?", 1) == 0 && ft_strlen(lex->content) >= 1)
				{
				if(lex->content[2])
					{
					ft_putstr_fd(ft_itoa(data->error_code), file);
					ft_putendl_fd(lex->content + 1, file);
					}
				else
					ft_putendl_fd(ft_itoa(data->error_code), file);
				}
				else
					ft_putendl_fd(getenv(lex->content), file);
				return (0);
			}
		else
			printf("$");
		}
		if(lex->type == 3 || lex->type == 5)
			break;
		if(lex->next)
			ft_putstr_fd(" ", file);
		lex = lex->next;
	}
	if(nl == 0)
		printf("\n");
	return (0);
}