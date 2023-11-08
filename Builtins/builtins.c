/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 16:39:22 by marvin            #+#    #+#             */
/*   Updated: 2023/11/06 17:46:58 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_exit2(t_lex *lex, t_global *data)
{
	printf("exit\n");
	if (lex->next == NULL)
		exit (data->error_code);
}

void	ft_exit(t_lex *lex, t_global *data)
{
	int	i;

	i = 0;
	ft_exit2(lex, data);
	if (lex->next->next && lex->next->type == 8 && lex->next->next->type == 8)
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		data->error_code = 1;
		return ;
	}
	else if (ft_check_nbr(lex->next->content) == 1 && \
		lex->next->content[0] != '+' && lex->next->content[0] != '-' && \
			lex->next->type == 8)
	{
		ft_putendl_fd("minishell: numeric argument required", 2);
		data->error_code = 2;
		
		exit (2);
	}
	if (lex->next->content[0] == '-')
	{
		i = ft_atoi(lex->next->content);
		i = 256 + i;
		exit(i);
	}
	exit (ft_atoi(lex->next->content));
}

int	ft_pwd(int file)
{
	char	*buf;

	buf = NULL;
	buf = getcwd(buf, 100);
	if (file != 1)
		dup2(file, STDOUT_FILENO);
	ft_putendl_fd(buf, file);
	free(buf);
	return (0);
}

int	ft_env(t_lex *lex, t_global *data, int file)
{
	int	i;

	i = 0;
	if (file != 1)
		dup2(file, STDOUT_FILENO);
	if (lex->next != NULL && lex->next->type != 1 && \
		lex->next->type != 3 && lex->next->type != 5)
	{
		ft_error("env: ", lex->next->content, \
			": No such file or directory\n", 1);
		return (127);
	}
	while (data->envmini[i] != NULL)
	{
		ft_putendl_fd(data->envmini[i], file);
		i++;
	}
	return (0);
}
