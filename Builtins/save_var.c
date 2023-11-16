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

t_lex	*record_exp(t_lex *lex)
{
	if (!lex->next)
		return (lex);
	while (lex->next)
	{
		if (ft_strchr(lex->content, 61) == 0)
			return (lex);
		lex = lex->next;
	}
	return (lex);
}

int	ft_save_env_exp2(t_global *data, t_lex *lex)
{
	int		l;
	int		ct;

	ct = 0;
	l = 0;
	if (!lex->next)
		return (1);
	while (lex)
	{
		l = 0;
		if (data->env_exp[0] != NULL)
		{
			while (data->env_exp[l] != NULL)
			{
				if (ft_strncmp(data->env_exp[l], lex->content, ft_strchri(lex->content, 61)) == 0)
					break;
				l++;
			}
		}
		if (data->env_exp[l] == NULL)
			ct++;
		lex = lex->next;
	}
	return (ct);
}

void	ft_save_env_exp(t_global *data, t_lex *lex)
{	
	char	**n_env;
	int 	l;
	int		i;
	int		j;
	int		count;

	count = ft_save_env_exp2(data, lex);
	j = 0;
	l = 0;
	if (!data->env_exp || !data->env_exp[0])
		data->env_exp[0] = NULL;
	n_env = malloc(sizeof(char *) * (count + (ft_strlen_char(data)) + 1));
	while (data->env_exp[l] != NULL)
	{
		n_env[j++] = ft_strdup(data->env_exp[l]);
		l++;
	}
	n_env[j] = NULL;
	if (data->env_exp || data->env_exp[0] != NULL)
		ft_free_split(data->env_exp);
	while (lex)
	{
		l = 0;
		i = 0;
		while (lex->content[i] != 61)
			i++;
		while (n_env[l])
		{
			if (ft_strncmp(n_env[l], lex->content, i) == 0)
			{
				free(n_env[l]);
				n_env[l] = ft_strdup(lex->content);
				break ;
			}
			l++;
		}
		if (n_env[l] == NULL)
		{
			n_env[j] = ft_strdup(lex->content);	
			n_env[j + 1] = NULL;
		}
		lex = lex->next;
	}
	data->env_exp = n_env;
}

int	verif_export(t_lex *lex)
{
	if (lex->next == NULL)
	{
		if (ft_strchr(lex->content, 61) == 0)
			return (1);
		else
			return (0);
	}
	while (lex->next != NULL)
	{
		lex = lex->next;
		if (ft_strchr(lex->content, 61) == 0)
			return (1);
	}
	return (0);
}

int	ft_export3(t_lex *lex, t_global *data, char **str)
{
	data->error_code = 0;
	if (ft_strchr(lex->content, 61) == 0)
		return (1);
	if (verif_export(lex) == 0)
	{
		ft_save_env_exp(data, lex);
		return (0);
	}
	if (lex->next != NULL)
	{
		lex = lex->next;
		ft_export3(lex, data, str);
	}
	return (0);
}
