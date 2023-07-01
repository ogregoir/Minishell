/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgreiner <rgreiner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 17:39:09 by rgreiner          #+#    #+#             */
/*   Updated: 2023/07/01 18:53:38 by rgreiner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_type(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (1);
		i++;
		
	}
	return (0);
}
char** ft_lexer(char **line, t_lex *lex)
{
	int	i;

	i = 0;
	while(line[i])
		lex->type = ft_check_type(line[i]);
	return (0);
	
}