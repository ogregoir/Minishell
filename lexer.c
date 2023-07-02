/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgreiner <rgreiner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 17:39:09 by rgreiner          #+#    #+#             */
/*   Updated: 2023/07/02 18:37:37 by rgreiner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lex	*ft_check_type(char *str)
{
	int	i;
	int j;
	t_lex *tmp;


	i = 0;
	j = 0;
	tmp = malloc(sizeof(t_lex));
	while(j < 6)
	{
		if(ft_strncmp(str, token[j].token, token[j].len) == 0)
			{
				tmp->content = ft_strdup(str);
				tmp->type = token[j].type;
				return(tmp) ;
			}
		j++;
	}
	tmp->content = ft_strdup(str);	
	tmp->type = TOKEN_TEXT;
	return(tmp) ;
}
t_lex	*ft_lexer(char **line, t_lex *lex)
{
	int	i;
	t_lex *tmp;

	i = 0;
	while(line[i])
	{
		tmp = ft_check_type(line[i]);
		printf("%s\n", tmp->content);
		printf("%d\n",tmp->type);
		tmp = tmp->next;
		i++;
	}
	return(lex) ;
}