/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgreiner <rgreiner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 16:25:53 by rgreiner          #+#    #+#             */
/*   Updated: 2023/10/20 18:09:30 by rgreiner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void	close_redi(int out, int file)
{
	if(file != 1)
	{
		dup2(out, STDOUT_FILENO);
		close(file);
		close(out);
	}
}

int		ft_search_token(t_lex *lex)
{
	t_lex *tmp;

	tmp = lex;
	while(tmp)
	{
		if(tmp->type == 1)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int		ft_multi_redi(t_lex *tmp)
{
	t_lex *tmp2;
	
	tmp2 = tmp;
	tmp2 = tmp2->next;
	while(tmp2)
	{
		if(tmp2->type == 1)
			return(1);
		if(tmp2->type == 3 || tmp2->type == 5)
			return(0);
		tmp2 = tmp2->next;
	}
	return(1);
}

int		ft_builtin_redi(t_lex *lex, int file, int child)
{
	t_lex *tmp;
	tmp = lex;
	
	while(tmp)
	{
		if(tmp->next && tmp->type == 3)
		{
			file = openfile(tmp->next->content, 1);
			if(ft_multi_redi(tmp) == 1)
				return(file);
			close(file);
		}
		if(tmp->next && tmp->type == 5)
		{	
			file = openfile(tmp->next->content, 0);
			if(ft_multi_redi(tmp) == 1)
				return(file);
			close(file);
		}
		if(tmp->next && tmp->type == 2)
		{
			if(access(tmp->next->content, F_OK | R_OK) != 0)
				ft_error(tmp->next->content, ": No such file or directory", child);			
		}
		if(tmp->type == 1)
			return(file);
		tmp = tmp->next;
	}
	return(1);
}