/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgreiner <rgreiner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 17:39:09 by rgreiner          #+#    #+#             */
/*   Updated: 2023/11/11 02:35:14 by rgreiner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*go_next(char *str, char *s)
{
	char	*ret;
	int		i;

	i = 0;
	ret = NULL;
	if (str == NULL)
		return (ret);
	while (str[i] && str[i] == s[i])
		i++;
	if (i >= 1)
		ret = ft_substr(str, i, ft_strlen(str));
	return (ret);
}

t_lex	*ft_check_type(char *str, t_lex *lex, int i, int j, t_global *data)
{
	char	*s;
	char	*next;

	s = NULL;
	next = NULL;
	if (str == NULL)
		return (lex);
	while (data->token[j].token != NULL)
	{
		if (ft_strncmp(str, data->token[j].token, data->token[j].len) == 0)
		{
			s = check_next(str, j, 0, data);
			if (!lex)
				lex = ft_lstnew(s, data->token[j].type);
			else
				addcontent(lex, s, data->token[j].type);
			next = go_next(str, s);
		//	if(str != NULL)
		//		free(str);
			if (next != NULL || s != NULL)
				lex = ft_check_type(next, lex, i, 0, data);
			if(next != NULL)
				free(next);
			return (lex);
		}
		j++;
	}
	lex = ft_text(s, str, j, lex, data);
	return (lex);
}

static int	copy_text(char *str)
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
	char *ret;
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
			if (j < 2 && ft_strncmp(str, data->token[j].token, data->token[j].len) == 0)
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
