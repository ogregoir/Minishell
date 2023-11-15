/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 20:13:47 by marvin            #+#    #+#             */
/*   Updated: 2023/10/26 20:13:47 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_already_exists(t_global *data, char *str, int i)
{
	int		j;

	j = 0;
	while (data->env_exp[j] != NULL)
	{
		if (ft_strncmp(data->env_exp[j], str, i) == 0)
			return (0);
		j++;
	}
	return (1);
}

int	ft_export(t_lex *lex, t_global *data)
{
	int	i;

	i = 0;
	if (!lex->next)
	{
		while (data->envmini[i] != NULL)
		{
			printf("declare -x %s\n", data->envmini[i]);
			i++;
		}
		return (0);
	}
	if (ft_isalpha(lex->next->content[0]) == 0)
		return (1);
	while (lex->next != NULL)
	{
		lex = lex->next;
		ft_export2(lex->content, data);
	}
	return (0);
}

int	ft_echo_nl(t_lex **lex)
{
	int	i;

	if (ft_strncmp((*lex)->content, "-n", 2) != 0)
		return (0);
	while (*lex)
	{
		i = 1;
		if (ft_strncmp((*lex)->content, "-n", 2) != 0)
			break ;
		while ((*lex)->content[i])
		{
			if ((*lex)->content[i] != 'n')
				return (0);
			i++;
		}
		if (i != 1)
			(*lex) = (*lex)->next;
	}
	return (1);
}

void	ft_echo2(t_lex *lex, int file, int nl)
{
	while (lex)
	{
		if (lex->next && lex->next->next && (lex->type == 3 || lex->type == 5))
			lex = lex->next->next;
		if (lex->type == 8)
		{
			ft_putstr_fd(lex->content, file);
			if (lex->next && (lex->next->type == 8 || lex->next->type == 2))
				ft_putstr_fd(" ", file);
		}
		if (lex->next && lex->type == 2)
			lex = lex->next;
		if (!lex->next || lex->type == 4)
			break ;
		lex = lex->next;
		if (lex->type == 3 || lex->type == 5 \
		|| lex->type == 1 || lex->type == 4)
			break ;
	}
	if (nl == 0)
	ft_putendl_fd("", file);
}

int	ft_echo(t_lex *lex, int file)
{
	int	nl;

	nl = 0;
	if (!lex->next)
	{
		printf("\n");
		return (0);
	}
	lex = lex->next;
	nl = ft_echo_nl(&lex);
	if (!lex)
		return (0);
	dup2(file, STDOUT_FILENO);
	ft_echo2(lex, file, nl);
	return (0);
}
