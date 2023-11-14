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

void	ft_save_env_exp3(t_global *data, t_lex *lex, int count)
{	
	char	**n_env;
	int 	l;
	int		i;
	int		j;

	j = 0;
	l = -1;
	n_env = malloc(sizeof(char *) * (count + ft_strlen_char(data) + 1));
	while (data->env_exp[++l])
		n_env[j++] = ft_strdup(data->env_exp[l]);
	n_env[j] = NULL;
	while (lex)
	{
		l = -1;
		i = 0;
		while (lex->content[i] != 61)
			i++;
		while (n_env[++l])
		{
			if (ft_strncmp(n_env[l], lex->content, i) == 0)
			{
				free(n_env[l]);
				n_env[l] = ft_strdup(lex->content);
				break ;
			}
		}
		if (n_env[l] == NULL)
			n_env[j++] = ft_strdup(lex->content);
		n_env[j] = NULL;
		lex = lex->next;
	}
	if (!n_env)
		return ;
	ft_free_split(data->env_exp);
	data->env_exp = n_env;
}

int	ft_save_env_exp2(t_global *data, t_lex *lex)
{
	int		l;
	int		count;

	l = 0;
	count = 0;
	while (lex)
	{
		while (data->env_exp[l])
		{		
			if (ft_strncmp(data->env_exp[l], lex->content, ft_strchri(lex->content, 61)) == 0)
				break;
			l++;
		}
		if (data->env_exp[l] == NULL)
			count++;
		lex = lex->next;
	}
	return (count);
}

void	ft_save_env_exp(t_global *data, t_lex *lex)
{
	int		count;
	int		i;

	count = 0;
	i = 0;
	count = ft_save_env_exp2(data, lex);
	printf("count = %d\n", count);
	ft_save_env_exp3(data, lex, count);
	while (data->env_exp[i++])
		printf("dt %s\n", data->env_exp[i]);
	//printf("lex->content %s\n", lex->content);
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
