/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgreiner <rgreiner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 17:39:09 by rgreiner          #+#    #+#             */
/*   Updated: 2023/07/03 11:56:45 by rgreiner         ###   ########.fr       */
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

void	check_next(char *str, int j)
{
	int i;
	int l;
	char *s;

	i = token[j].len;
	l = 0;
	s = ft_substr(str, i, ft_strlen(str));
	while(s[l])
	{
		if(ft_isalnum(s[l]) == 0)
			break;
		l++;
	}
	free(s);
	s = ft_substr(str, l + 1, ft_strlen(str));
	printf("substr = %s\n", s);
	
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
				check_next(str, j);
				s = ft_strdup(str);
				if (!lex)
					lex = ft_lstnew(s, token[j].type);
				else
					addcontent(lex, s, token[j].type);
				return(lex) ;
			}
		j++;
	}	
	s = ft_strdup(str);
	if (!lex)
		lex = ft_lstnew(s, TOKEN_TEXT);
	else
		addcontent(lex, s, TOKEN_TEXT);
	return(lex) ;
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
