/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgreiner <rgreiner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 10:11:22 by rgreiner          #+#    #+#             */
/*   Updated: 2023/11/16 15:49:47 by rgreiner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_redi_out(t_lex *lex)
{
	t_lex	*tmp;

	tmp = lex;
	while (tmp)
	{
		if (tmp->type == 3 || tmp->type == 5)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	check_redi(t_lex *lex)
{
	t_lex	*tmp;

	tmp = lex;
	while (tmp)
	{
		if (tmp->type == 3 || tmp->type == 5 || \
			tmp->type == 2 || tmp->type == 4)
			return (1);
		if (tmp->type == 1)
			return (0);
		tmp = tmp->next;
	}
	return (0);
}

int	openfile(char *content, int mod)
{
	int	file;

	if (access(content, F_OK) == 0)
		if (access(content, W_OK | R_OK) != 0)
			ft_error(content, ": Permission denied", "", 0);
	if (mod == 0)
		file = open(content, O_APPEND | O_WRONLY | O_CREAT, 0644);
	if (mod == 1)
		file = open(content, O_TRUNC | O_WRONLY | O_CREAT, 0644);
	return (file);
}
