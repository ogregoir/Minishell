/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgreiner <rgreiner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 14:07:53 by rgreiner          #+#    #+#             */
/*   Updated: 2023/09/27 20:54:01 by rgreiner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"


void free_list(t_lex *lex)
{
    while(lex->next)
    {
        free(lex->content);
        lex = lex->next;
    }
    free(lex->content);
}

char *ft_last_ele(t_lex *lex)
{
	char *ret;
	t_lex *tmp;

	tmp = lex;
	while(tmp->next)
		tmp = tmp ->next;
	ret = ft_strdup(tmp->content);
	return(ret);
}