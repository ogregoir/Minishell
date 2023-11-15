/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_var.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 19:42:15 by marvin            #+#    #+#             */
/*   Updated: 2023/10/26 19:42:15 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_verif_exp(t_lex *lex, t_global *data)
{
	data->error_code = 0;
	if (ft_strchri(lex->content, 61) == -1)
	{
		data->error_code = 1;
		if (lex->type == 1)
		{
			if (lex->next != NULL)
				ft_error(": cannot acces", lex->content, NULL, 1);
			data->error_code = 2;
			return (data->error_code);
		}
		return (data->error_code);
	}
	return (data->error_code);
}

void	ft_save_env_exp2(t_global *data, char **str, int j, int i)
{
	int		l;

	l = 0;
	while (data->env_exp[l])
	{
		if (ft_strncmp(str[j], data->env_exp[l], i) == 0)
		{
			free (data->env_exp[l]);
			data->env_exp[l] = ft_strdup(str[j]);
		}
		l++;
	}
	if (data->env_exp[l] == NULL)
	{
		data->env_exp[l] = ft_strdup(str[j]);
		data->env_exp[l + 1] = NULL;
	}
}

void	ft_save_env_exp(t_global *data, char **str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[j] != NULL)
	{
		while (str[j][i] != 61)
			i++;
		ft_save_env_exp2(data, str, j, i);
		j++;
	}
}

int	ft_export3(t_global *data, t_lex *lex, char **str)
{
	if (ft_verif_exp(lex, data) == 1)
	{
		if (lex->type == 1)
		{
			ft_error(lex->content, ": command not found", NULL, 1);
			return (1);
		}
		return (2);
	}
	ft_save_env_exp(data, str);
	if (lex->next != NULL)
	{
		lex = lex->next;
		ft_export3(data, lex, str);
	}
	return (0);
}
