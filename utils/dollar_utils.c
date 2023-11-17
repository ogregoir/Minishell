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

void	dollar_lexer2(t_lex *lex, t_global *data, t_lex **tmp, char *tmp2)
{
	if (ft_strlen(lex->content) == 1)
	{
		if (!(*tmp))
			(*tmp) = ft_lstnew(ft_strdup("$"), 8);
		else
			addcontent((*tmp), ft_strdup("$"), 8);
	}
	else
	{
		tmp2 = ft_convert_dollar(lex->content, 0, data);
		if (tmp2 == NULL)
			return ;
		if (!(*tmp))
			(*tmp) = ft_lstnew(tmp2, 8);
		else
			addcontent((*tmp), tmp2, 8);
	}
}

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
			dollar_lexer2(lex, data, &tmp, tmp2);
		else
		{
			tmp2 = ft_strdup(lex->content);
			if (!tmp)
				tmp = ft_lstnew(tmp2, lex->type);
			else
				addcontent(tmp, tmp2, lex->type);
		}
		lex = lex->next;
	}
	ft_free_list(tofree);
	return (tmp);
}

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

int	check_err(t_lex *lex)
{
	t_lex	*tmp;

	tmp = lex;
	while (tmp->next)
		tmp = tmp->next;
	if (tmp->type == 1)
	{
		ft_error("", "", "syntax error near unexpected token `|'", 1);
		return (1);
	}
	return (0);
}
