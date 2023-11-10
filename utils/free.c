/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 05:12:25 by marvin            #+#    #+#             */
/*   Updated: 2023/11/10 05:12:25 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free_list(t_lex *lex)
{
	t_lex	*tmp;

	while (lex != NULL)
	{
		tmp = lex;
		lex = lex->next;
		free(tmp);
	}
}

void	print_lexer(t_lex *lex)
{
	t_lex	*tmp;

	tmp = lex;
	while (tmp)
	{
		printf("-------------------\n");
		printf("%s\n", tmp->content);
		printf("%u\n", tmp->type);
		printf("-------------------\n");
		tmp = tmp->next;
	}
}

void	ft_free_char(t_global *data)
{
	int	i;

	i = 0;
	if (!data->envmini || data->envmini[i] == NULL)
		return ;
	while (data->envmini[i])
	{
		free(data->envmini[i]);
		i++;
	}
	i = 0;
	if (data->env_exp || data->env_exp[i] == NULL)
		return ;
	while (data->env_exp[i])
	{
		free(data->env_exp);
		i++;
	}
}

void ft_free_global(t_global *data)
{
	int i;
	
	i = 0;
	while (i <= 8)
	{
		free (data->token[i].token);
		i++;
	}
}
