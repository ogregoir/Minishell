/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgreiner <rgreiner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 17:35:07 by rgreiner          #+#    #+#             */
/*   Updated: 2023/11/17 01:10:15 by rgreiner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_malloc_quote(char *line)
{
	int		j;
	int		i;

	j = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == 34)
			j++;
		else if (line[i] == 39)
			j++;
		else if (line[i] == ' ')
			j++;
		i++;
	}
	return (j);
}

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

void	init_quotes(t_quotes *q, char *line)
{
	q->i = 0;
	q->j = ft_malloc_quote(line);
	q->str = malloc(sizeof(char *) * (q->j + 1));
	q->j = 0;
}

char	*ft_quotes2(t_lex **lex, char *line, t_global *data, t_quotes **q)
{
	(*q)->str[(*q)->j] = ft_check_quote(line, (*q)->i);
	if (!(*lex) && line[(*q)->i] == 34 \
	&& ft_strchri((*q)->str[(*q)->j], '$') >= 0 && \
		ft_strlen((*q)->str[(*q)->j]) > 1)
		(*lex) = ft_lstnew((*q)->str[(*q)->j], 0);
	else if (line[(*q)->i] == 34 && ft_strchri((*q)->str[(*q)->j], '$') >= 0 && \
	ft_strlen((*q)->str[(*q)->j]) > 1)
		addcontent((*lex), (*q)->str[(*q)->j], 0);
	else if (line[(*q)->i] != 34 && line[(*q)->i] != 39)
		(*lex) = ft_lexer_quotes((*q)->str[(*q)->j], (*lex), (*q)->i, data);
	else if (!(*lex) && (*q)->str[(*q)->j])
		(*lex) = ft_lstnew((*q)->str[(*q)->j], 8);
	else if ((*q)->str[(*q)->j])
		addcontent((*lex), (*q)->str[(*q)->j], 8);
	(*q)->j++;
	if (line[(*q)->i] == 34 || line[(*q)->i] == 39)
		(*q)->i = ft_strlen((*q)->str[(*q)->j - 1]) + 2;
	else
		(*q)->i = ft_strlen((*q)->str[(*q)->j - 1]);
	line = ft_substrfree(line, (*q)->i, ft_strlen(line));
	return (line);
}

t_lex	*ft_quote(char *line, t_lex *lex, t_global *data, t_quotes *q)
{
	init_quotes(q, line);
	while (line[q->i] != '\0')
	{
		if (line[q->i] == ' ')
		{
			q->i++;
			q->str[q->j] = ft_strdup(" ");
			if (!lex)
				lex = ft_lstnew(q->str[q->j], 8);
			else
				addcontent(lex, q->str[q->j], 8);
			line = ft_substrfree(line, q->i, ft_strlen(line));
			q->i = 0;
		}
		if (line[q->i] == '\0')
			break ;
		line = ft_quotes2(&lex, line, data, &q);
		if ((line[0] == 34 || line[0] == 39) && ft_strlen(line) == 1)
			break ;
		q->i = 0;
	}
	free(q->str);
	free(line);
	free(q);
	return (lex);
}
