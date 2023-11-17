/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgreiner <rgreiner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 17:35:07 by rgreiner          #+#    #+#             */
/*   Updated: 2023/11/17 13:37:37 by rgreiner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

char	*ft_join2(t_lex **lex, t_global *data, char *str, t_lex **tmp)
{
	if ((*lex)->type == 0 && ft_strncmp((*lex)->content, "?", 1) && \
		ft_strlen((*lex)->content) == 1)
		(*tmp) = check_dollar((*tmp), data, "?");
	else if ((*lex)->next && \
			ft_strncmp((*lex)->next->content, " ", 1) == 0 && \
			ft_strlen((*lex)->next->content) == 1)
	{
		if (!(*tmp))
			(*tmp) = ft_lstnew(ft_strdup((*lex)->content), (*lex)->type);
		else
			addcontent((*tmp), ft_strdup((*lex)->content), (*lex)->type);
	}
	else if ((*lex)->next)
	{
		str = ft_strjoin((*lex)->content, (*lex)->next->content);
		if (!(*tmp))
			(*tmp) = ft_lstnew(str, (*lex)->type);
		else
			addcontent((*tmp), str, (*lex)->type);
		(*lex) = (*lex)->next;
	}
	while ((*lex)->next && ft_strncmp((*lex)->content, " ", 1) == 0 && \
		ft_strlen((*lex)->content) == 1 && (*lex)->type != 0)
		(*lex) = (*lex)->next;
	return (str);
}

t_lex	*ft_join3(t_lex *lex, t_lex *tmp, char *str)
{
	if (lex->content[0] == 32)
		return (tmp);
	if (!str)
	{
		if (!tmp)
			tmp = ft_lstnew(ft_strdup(lex->content), lex->type);
		else
			addcontent(tmp, ft_strdup(lex->content), lex->type);
		return (tmp);
	}
	if (!tmp && ft_last_ele(tmp, str) == 1)
		tmp = ft_lstnew(ft_strdup(lex->content), lex->type);
	else if (ft_last_ele(tmp, str) == 1)
		addcontent(tmp, ft_strdup(lex->content), lex->type);
	return (tmp);
}

t_lex	*ft_join4(t_lex *tmp, t_lex *lex, char *str, t_lex *tofree)
{
	tmp = ft_join3(lex, tmp, str);
	ft_free_list(tofree);
	return (tmp);
}

t_lex	*ft_join(t_lex *tofree, t_global *data, t_lex *tmp, t_lex *lex)
{
	char	*str;

	str = NULL;
	while (lex->next)
	{
		while (lex->next && ft_strncmp(lex->content, " ", 1) == 0 && \
			ft_strlen(lex->content) == 1 && lex->type != 0)
			lex = lex->next;
		if ((ft_strncmp(lex->content, " ", 1) != 0) && \
			(lex->type == 8 || lex->type == 0))
			str = ft_join2(&lex, data, str, &tmp);
		else if (lex->type == 0 && \
			ft_strncmp(lex->content, "?", 1) && ft_strlen(lex->content) == 1)
			tmp = check_dollar(tmp, data, "?");
		else if (!tmp && (ft_strncmp(lex->content, " ", 1) != 0 || \
			ft_strlen(lex->content) != 1))
			tmp = ft_lstnew(ft_strdup(lex->content), lex->type);
		else if (ft_strncmp(lex->content, " ", 1) != 0 || \
			ft_strlen(lex->content) != 1)
			addcontent(tmp, ft_strdup(lex->content), lex->type);
		if (lex->next)
			lex = lex->next;
	}
	tmp = ft_join4(tmp, lex, str, tofree);
	return (tmp);
}
