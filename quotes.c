/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgreiner <rgreiner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 17:35:07 by rgreiner          #+#    #+#             */
/*   Updated: 2023/11/17 15:06:28 by rgreiner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_check_quote(char *line, int i)
{
	char	*str;

	if (line[i] == 34)
	{
		str = ft_search_quote(line, 34, 0);
		return (str);
	}
	else if (line[i] == 39)
	{
		str = ft_search_quote(line, 39, 0);
		return (str);
	}
	else
	{
		while (line[i])
		{
			if (line[i] == ' ' || line[i] == 34 || line [i] == 39)
			{
				str = ft_substr(line, 0, i);
				return (str);
			}
			i++;
		}
	}
	return (line);
}

char	*ft_quotes2(t_lex **lex, char *line, int i, t_global *data)
{
	char	*tmp;

	tmp = ft_check_quote(line, i);
	if (tmp[0] != 0)
	{
		if (!(*lex) && line[i] == 34 && ft_strchri(tmp, '$') \
		>= 0 && ft_strlen(tmp) > 1)
			(*lex) = ft_lstnew(ft_strdup(tmp), 0);
		else if (line[i] == 34 && ft_strchri(tmp, '$') >= 0 \
		&& ft_strlen(tmp) > 1)
			addcontent((*lex), ft_strdup(tmp), 0);
		else if (line[i] != 34 && line[i] != 39)
			(*lex) = ft_lexer_quotes(tmp, (*lex), i, data);
		else if (!(*lex) && tmp)
			(*lex) = ft_lstnew(ft_strdup(tmp), 8);
		else if (tmp)
			addcontent((*lex), ft_strdup(tmp), 8);
	}
	if (line[i] == 34 || line[i] == 39)
		i = ft_strlen(tmp) + 2;
	else
		i = ft_strlen(tmp);
	if (ft_strcmp(tmp, line) != 0)
		free(tmp);
	return (ft_substrfree(line, i, ft_strlen(line)));
}

t_lex	*ft_quote(char *line, t_lex *lex, int i, t_global *data)
{
	while (line[i] != '\0')
	{
		if (line[i] == ' ')
		{
			i++;
			if (!lex)
				lex = ft_lstnew(ft_strdup(" "), 8);
			else
				addcontent(lex, ft_strdup(" "), 8);
			line = ft_substrfree(line, i, ft_strlen(line));
			i = 0;
		}
		if (line[i] == '\0')
			break ;
		line = ft_quotes2(&lex, line, i, data);
		if ((line[0] == 34 || line[0] == 39) && ft_strlen(line) == 1)
			break ;
		i = 0;
	}
	free(line);
	return (lex);
}
