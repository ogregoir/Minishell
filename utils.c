/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgreiner <rgreiner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 18:08:02 by rgreiner          #+#    #+#             */
/*   Updated: 2023/11/17 01:23:29 by rgreiner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_search_quote(char *line, char c, int i)
{
	char	*str;
	int		j;

	while (line[i])
	{
		if (line[i] == c)
		{
			j = i;
			while (line[i])
			{
				i++;
				if (line[i] == c)
				{
					if (line[j + 1] == '$' && c == 39)
						str = ft_substr(line, j + 1, i - 1);
					else
						str = ft_substr(line, j + 1, i - 1);
					return (str);
				}
			}
		}
		else
			i++;
	}
	return (line);
}

int	check_text(int text)
{
	if (text == '<')
		return (1);
	if (text == '>')
		return (1);
	if (text == '|')
		return (1);
	if (text == '$')
		return (1);
	return (0);
}

t_lex	*ft_text(char *str, int j, t_lex *lex, t_global *data)
{
	char	*new;
	char	*s;

	new = NULL;
	s = check_next(str, j, 0, data);
	if (!s)
		return (lex);
	if (!lex)
		lex = ft_lstnew(s, TOKEN_TEXT);
	else
		addcontent(lex, s, TOKEN_TEXT);
	new = go_next(str, s);
	if (ft_strlen(new) == 0)
	{
		free(new);
		return (lex);
	}
	if (new != NULL || s != NULL)
		lex = ft_check_type(new, lex, 0, data);
	free(new);
	return (lex);
}
