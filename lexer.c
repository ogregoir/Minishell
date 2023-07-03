/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgreiner <rgreiner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 17:39:09 by rgreiner          #+#    #+#             */
/*   Updated: 2023/07/03 18:53:26 by rgreiner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_space(char *str, int	j)
{
	int		i;
	char	*s;

	i = 0;
	while (str[i])
	{	
		if ((ft_strncmp(str, token[j].token, token[j].len)) || (str[i] == ' '))
		{
			s = ft_strndup(str, i);
			return (s);
		}
		i++;
	}
	return (str);
}
/*
void	check_type(char	*str, char c)
{
	int		j;
	int		i;
	char	*s;
	t_lex 	*tmp;

	j = 0;
	s = str;
	tmp = malloc(sizeof(t_lex));
	str = check_space(str, token[j].token);
	while (str[i])
	{	
		if ()
			tmp->
}*/

char	*go_next(char *str, char *s)
{
	char *ret;
	int i;
	
	i = 0;
	ret = NULL;
	if(str == NULL)
		return(ret);
	while (str[i] && str[i] == s[i])
		i++;
	ret = ft_substr(str, i, ft_strlen(str));
	return (ret);
}

t_lex	*ft_check_type(char *str, t_lex *lex)
{
	int	i;
	int j;
	char *s;

	i = 0;
	j = 0;
	while(token[j].token != NULL)
	{
		if(ft_strncmp(str, token[j].token, token[j].len) == 0)
			{	
				s = check_next(str, j);
				if(s == NULL)
					return (lex);
				str = go_next(str, s);
				if(str == NULL)
					return (lex);
				if (!lex)
					lex = ft_lstnew(s, token[j].type);
				else
					addcontent(lex, s, token[j].type);
				lex = ft_check_type(str, lex);
				return (lex);
			}
		j++;
	}
	s = check_next(str, j);
	if(s == NULL && str != NULL)
		{
		if (!lex)
			lex = ft_lstnew(str, TOKEN_TEXT);
		else
			addcontent(lex, str, TOKEN_TEXT);
		return (lex);
		}
	str = go_next(str, s);
	if(str == NULL)
		return (lex);
	if (!lex)
		lex = ft_lstnew(s, TOKEN_TEXT);
	else
		addcontent(lex, s, TOKEN_TEXT);
	lex = ft_check_type(str, lex);
	return(lex) ;
}

char	*check_next(char *str, int j)
{
	int i;
	int l;
	char *s;

	i = token[j].len;
	l = 0;
	s = NULL;
	while(str[l])
	{
		if(ft_isalnum(str[l]) == 0)
		{
			if(l == 0)
				s = ft_substr(str, 0, l + 1);
			else
				s = ft_substr(str, 0, l);
			return (s);
		}
		l++;
	}
	return (s);
}

t_lex	*ft_lexer(char **line, t_lex *lex)
{
	int	i;

	i = 0;
	lex = NULL;
	while(line[i])
	{
		lex = ft_check_type(line[i], lex);
		i++;
	}
	return(lex) ;
}
