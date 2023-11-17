/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgreiner <rgreiner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 17:39:09 by rgreiner          #+#    #+#             */
/*   Updated: 2023/11/17 11:12:34 by rgreiner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_check_type2(char *str, int j, t_global *data, t_lex **lex)
{
	char	*next;
	char	*s;
	int		i;

	next = NULL;
	s = NULL;
	i = 0;
	s = check_next(str, j, 0, data);
	if (!(*lex))
		(*lex) = ft_lstnew(s, data->token[j].type);
	else
		addcontent((*lex), s, data->token[j].type);
	next = go_next(str, s);
	if (next != NULL || s != NULL)
		(*lex) = ft_check_type(next, (*lex), i, data);
	if (next != NULL)
		free(next);
}

t_lex	*ft_check_type(char *str, t_lex *lex, int j, t_global *data)
{
	if (str == NULL)
		return (lex);
	while (data->token[j].token != NULL)
	{
		if (ft_strncmp(str, data->token[j].token, data->token[j].len) == 0)
		{
			ft_check_type2(str, j, data, &lex);
			return (lex);
		}
		j++;
	}
	lex = ft_text(str, j, lex, data);
	return (lex);
}

int	copy_text(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (ft_isalnum(str[i]) == 0 && str[i] != ' ' && \
			str[i] != 47 && check_text(str[i]) == 1)
			return (i);
		i++;
	}
	return (0);
}

char	*check_next2(char *str, int l)
{
	char	*ret;

	l = copy_text(str);
	if (l == 0)
		return (ft_strdup(str));
	else
	{
		ret = ft_substr(str, 0, l);
		return (ret);
	}
	return (NULL);
}

char	*check_next(char *str, int j, int l, t_global *data)
{
	char	*s;

	s = NULL;
	while (str[l])
	{
		if (ft_isalnum(str[l]) == 0 && str[l] != ' ' \
		&& str[l] != 47 && check_text(str[l]) == 1)
		{
			if (j < 2 && ft_strncmp(str, data->token[j].token, \
			data->token[j].len) == 0)
				l++;
			if (j == 2)
				return (ft_strdup(str));
			s = ft_substr(str, 0, l + 1);
			return (s);
		}
		else
			return (check_next2(str, l));
		l++;
	}
	return (s);
}
