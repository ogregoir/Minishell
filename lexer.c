/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogregoir <ogregoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 17:39:09 by rgreiner          #+#    #+#             */
/*   Updated: 2023/07/02 21:12:27 by ogregoir         ###   ########.fr       */
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

t_lex	*ft_check_type(char *str, t_lex *lex)
{
	int	i;
	int j;
	char *s;

	i = 0;
	j = 0;
	while(j < 6)
	{
		if(ft_strncmp(str, token[j].token, token[j].len) == 0)
			{
				s = ft_strdup(str);
				if (!lex)
					lex = ft_lstnew(s, j);
				else
					addcontent(lex, s, j);
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
		//printf("%s\n", lex->content);
		//printf("%d\n",lex->type);
		i++;
	}
	return(lex) ;
}
