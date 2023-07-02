/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgreiner <rgreiner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 17:39:09 by rgreiner          #+#    #+#             */
/*   Updated: 2023/07/02 14:34:42 by rgreiner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_check_type(char *str, t_lex *lex, char c, int type)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
		{	
			lex->type = type;
			lex->content = ft_strdup(str);
			return ;
		}
		i++;
	}
	return ;
}
void	ft_lexer(char **line, t_lex *lex)
{
	int	i;
	t_lex *tmp;

	i = 0;
	while(line[i])
	{
		ft_check_type(line[i], lex, '$', 0);
		i++;
	}
	tmp = lex;
	if(lex->type == TOKEN_DOLLAR)
		printf("%u\n",tmp->type);
	else
		printf("test");
	return ;
	
}