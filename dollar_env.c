/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 03:06:33 by marvin            #+#    #+#             */
/*   Updated: 2023/10/27 03:06:33 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_dollar(t_lex *lex, t_global *data)
{
	int		l;

	l = 1;
	if (lex->content[0] == '?' && lex->content[1] != '\0')
	{
		printf("%d", data->error_code);
		while (lex->content[l] != '\0')
		{
			if (lex->content[l] == '$' && lex->content[l + 1] == '?')
			{
				printf("%d", data->error_code);
				l += 2;
			}
			else
			{
				printf("%c", lex->content[l]);
				l++;
			}
		}
		printf("\n");
	}
}

char	*ft_dollar_env2(t_global *data, t_lex *lex, int j)
{
	char	*str;
	int		i;

	str = NULL;
	i = 0;
	while (data->envmini[i])
	{
		if (ft_strncmp(data->envmini[i], lex->content, j) == 0)
			str = getenv(lex->content);
		i++;
	}
	if (str == NULL)
		return (NULL);
	i = 0;
	while (str[i] != 32)
		i++;
	str = ft_substr(str, 0, i);
	return (str);
}

int	ft_error_da(char *str)
{
	ft_error(str, NULL, NULL, 1);
	return (127);
}

int	ft_dollar_env(t_lex *lex, t_global *data)
{
	int		j;

	j = ft_strlen(lex->content);
	if (ft_strncmp(lex->content, "?", 1) == 0)
	{
		if (j == 1)
		{
			printf("%d\n", data->error_code);
			return (0);
		}
		else
		{
			ft_print_dollar(lex, data);
		}
	}
	if (j == 1 && ft_strncmp(lex->content, "$", 1) == 0)
		return (ft_error_da("$: command not found\n"));
	if (ft_strchr(lex->content, 48) != 0)
		return (ft_error_da("Command '-minishell' not found\n"));
	if (ft_dollar_env2(data, lex, j) == 0)
		return (0);
	return (ft_dollar_access(ft_dollar_env2(data, lex, j)));
}
