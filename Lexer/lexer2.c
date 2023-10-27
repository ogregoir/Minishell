/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 17:35:07 by rgreiner          #+#    #+#             */
/*   Updated: 2023/10/27 14:59:50 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_lex	*ft_text(char *s, char *str, int j, t_lex *lex, t_global *data)
{
	s = check_next(str, j, 0, data);
	if (s == NULL)
		return (lex);
	if (!lex)
		lex = ft_lstnew(s, TOKEN_TEXT);
	else
		addcontent(lex, s, TOKEN_TEXT);
	str = go_next(str, s);
	if (str != NULL || s != NULL)
		lex = ft_check_type(str, lex, 0, 0, data);
	return (lex);
}

int	check_text(int text)
{
	if (text == '<')
		return (1);
	if (text == '>')
		return (1);
	if (text == '|')
		return (1);
	if (text == '$')
		return (1);
	return (0);
}

int	ft_nbr_space(char **str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i][0] == '\0')
			j++;
		i++;
	}
	return (j);
}

t_lex	*ft_join(t_lex *lex, t_global *data)
{
	t_lex	*tmp;
	char	*str;

	tmp = NULL;
	while (lex->next)
	{
		while (lex->next && ft_strncmp(lex->content, " ", 1) == 0 && \
			ft_strlen(lex->content) == 1 && lex->type != 0)
			lex = lex->next;
		if ((ft_strncmp(lex->content, " ", 1) != 0) && \
			(lex->type == 8 || lex->type == 0))
		{
			if (lex->type == 0 && ft_strncmp(lex->content, "?", 1) && \
				ft_strlen(lex->content) == 1)
				tmp = check_dollar(tmp, data, "?");
			else if (lex->next && \
				ft_strncmp(lex->next->content, " ", 1) == 0 && \
					ft_strlen(lex->next->content) == 1)
			{
				if (!tmp)
					tmp = ft_lstnew(lex->content, lex->type);
				else
					addcontent(tmp, lex->content, lex->type);
			}
			else if (lex->next)
			{
				str = ft_strjoin(lex->content, lex->next->content);
				if (!tmp)
					tmp = ft_lstnew(str, lex->type);
				else
					addcontent(tmp, str, lex->type);
				lex = lex ->next;
			}
			while (lex->next && ft_strncmp(lex->content, " ", 1) == 0 && \
				ft_strlen(lex->content) == 1 && lex->type != 0)
				lex = lex->next;
		}
		else if (lex->type == 0 && \
			ft_strncmp(lex->content, "?", 1) && ft_strlen(lex->content) == 1)
			tmp = check_dollar(tmp, data, "?");
		else if (!tmp && (ft_strncmp(lex->content, " ", 1) != 0 || \
			ft_strlen(lex->content) != 1))
			tmp = ft_lstnew(lex->content, lex->type);
		else if (ft_strncmp(lex->content, " ", 1) != 0 || \
			ft_strlen(lex->content) != 1)
			addcontent(tmp, lex->content, lex->type);
		if (lex->next)
			lex = lex->next;
	}
	if (ft_strncmp(lex->content, " ", 1) == 0 && \
		ft_strlen(lex->content) == 1)
		return (tmp);
	if (lex->type == 0 && \
		ft_strncmp(lex->content, "?", 1) && ft_strlen(lex->content) == 1)
		tmp = check_dollar(tmp, data, "?");
	else if (!tmp && ft_strncmp(ft_last_ele(tmp), str, ft_strlen(str) != 0))
		tmp = ft_lstnew(lex->content, lex->type);
	else if (ft_strncmp(ft_last_ele(tmp), str, ft_strlen(str) != 0))
		addcontent(tmp, lex->content, lex->type);
	return (tmp);
}
