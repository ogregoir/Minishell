/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexerquotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 13:23:43 by rgreiner          #+#    #+#             */
/*   Updated: 2023/10/27 15:01:40 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_lex	*ft_lexer_quotes2(t_lex *lex, char *s, int j, t_global *data)
{
	if (!lex)
		lex = ft_lstnew(s, data->token[j].type);
	else
		addcontent(lex, s, data->token[j].type);
	return (lex);
}

t_lex	*ft_lexer_quotes(char *line, t_lex *lex, int i, t_global *data)
{
	int		j;
	char	*s;

	j = 0;
	i = 0;
	s = NULL;
	if (i == 0)
	{
		while (data->token[j].token != NULL)
		{
			if (ft_strncmp(line, data->token[j].token, data->token[j].len) == 0)
			{
				s = check_next(line, j, 0, data);
				lex = ft_lexer_quotes2(lex, s, j, data);
				line = go_next(line, s);
				if (line != NULL || s != NULL)
					lex = ft_check_type(line, lex, i, 0, data);
				return (lex);
			}
			j++;
		}
		lex = ft_text(s, line, j, lex, data);
	}
	return (lex);
}
