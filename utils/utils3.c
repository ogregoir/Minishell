/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 00:50:03 by marvin            #+#    #+#             */
/*   Updated: 2023/10/25 00:50:03 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_last_ele(t_lex *lex, char *str)
{
	char	*ret;
	t_lex	*tmp;

	tmp = lex;
	while (tmp->next)
		tmp = tmp->next;
	ret = ft_strdup(tmp->content);
	if (ft_strncmp(ret, str, ft_strlen(str) != 0))
	{
		free(ret);
		return (1);
	}
	free(ret);
	return (0);
}

int	ft_variable_exist(t_global *data, char *str)
{
	int	i;

	i = 0;
	while (data->envmini[i])
	{
		if (ft_strncmp(data->envmini[i], str, ft_strlen(str)) == 0)
			return (0);
		i++;
	}
	return (1);
}

char	*ft_strdup2(const char *src, int n)
{
	char	*tab;
	int		i;

	i = 0;
	tab = malloc(sizeof(char *) * (ft_strlen(src) -n + 1));
	while (src[i])
	{
		tab[i] = src[n];
		i++;
		n++;
	}
	tab[i] = '\0';
	return (tab);
}

char	*ft_strncpy(char *str, char *src, int i)
{
	char	*dest;

	dest = str;
	while (i > 0 && *src != '\0')
	{
		*dest = *src;
		dest++;
		src++;
		i--;
	}
	while (i > 0)
	{
		*dest = '\0';
		dest++;
		i--;
	}
	return (str);
}

int	ft_strlen_char(t_global *data)
{
	int	i;

	i = 0;
	while (data->env_exp[i])
		i++;
	return (i);
}
