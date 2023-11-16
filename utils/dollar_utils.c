/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 01:33:10 by marvin            #+#    #+#             */
/*   Updated: 2023/10/27 01:33:10 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_lex	*dollar_lexer(t_lex *tofree, t_global *data)
{
	char	*tmp2;
	t_lex	*tmp;
	t_lex	*lex;

	tmp = NULL;
	lex = tofree;
	while (lex)
	{
		if (lex->type == 0)
		{
			if (ft_strlen(lex->content) == 1)
			{
				if (!tmp)
					tmp = ft_lstnew(ft_strdup("$"), 8);
				else
					addcontent(tmp, ft_strdup("$"), 8);
			}
			else
			{
				tmp2 = ft_convert_dollar(lex->content, 0, data);
				if (!tmp)
					tmp = ft_lstnew(tmp2, 8);
				else
					addcontent(tmp, tmp2, 8);
			}
		}
		else
		{
			tmp2 = ft_strdup(lex->content);
			if(!tmp)
				tmp = ft_lstnew(tmp2, lex->type);
			else
				addcontent(tmp, tmp2, lex->type);
		}
		lex = lex->next;
	}
	ft_free_list(tofree);
	return (tmp);
}
