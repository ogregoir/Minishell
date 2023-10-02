/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexerquotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 13:23:43 by rgreiner          #+#    #+#             */
/*   Updated: 2023/10/02 00:26:55 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

t_lex *ft_lexer_quotes(char *line, t_lex *lex, int i)
{
    int j;
    char *s;

    j = 0;
    i = 0;
	s = NULL;
    if(i == 0)
    {
	while (g_token[j].token != NULL)
    {
        if (ft_strncmp(line, g_token[j].token, g_token[j].len) == 0)
		{
            s = check_next(line, j, 0);
			if (!lex)
				lex = ft_lstnew(s, g_token[j].type);
			else
				addcontent(lex, s, g_token[j].type);
            line = go_next(line, s);
			if (line != NULL || s != NULL)
				lex = ft_check_type(line, lex, i, 0);
			return (lex);
		}
		j++;
	}
	lex = ft_text(s, line, j, lex);
    }
	return (lex);
}