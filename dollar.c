/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgreiner <rgreiner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 18:08:02 by rgreiner          #+#    #+#             */
/*   Updated: 2023/08/24 18:37:55 by rgreiner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_dollar(t_lex *lex)
{
    if(!lex->next)
        {
            printf("$: command not found\n");
            return ;
        }
    if(ft_strncmp(lex->next->content, "?", 1) == 0 && ft_strlen(lex->next->content) == 1)
        {
            printf("%d: command not found\n", error_code);
            error_code = 127;
            return;
        }
}