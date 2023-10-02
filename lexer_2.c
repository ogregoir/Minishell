/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 17:35:07 by rgreiner          #+#    #+#             */
/*   Updated: 2023/10/02 00:26:40 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lex	*ft_text(char *s, char *str, int j, t_lex *lex)
{
	s = check_next(str, j, 0);
	if (s == NULL)
		return (lex);
	if (!lex)
		lex = ft_lstnew(s, TOKEN_TEXT);
	else
		addcontent(lex, s, TOKEN_TEXT);
	str = go_next(str, s);
	if (str != NULL || s != NULL)
		lex = ft_check_type(str, lex, 0, 0);
	return (lex);
}

int	check_text(int text)
{
	if(text == '<')
		return(1);
	if(text == '>')
		return(1);
	if(text == '|')
		return(1);
	if(text == '$')
		return(1);
	return(0);
}