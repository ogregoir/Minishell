/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 18:08:02 by rgreiner          #+#    #+#             */
/*   Updated: 2023/09/21 18:50:11 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_dollar(t_lex *lex)
{
	if (!lex->next)
	{
		printf("$: command not found\n");
		return ;
	}
	if (ft_strncmp(lex->next->content, "?", 1) == 0 && ft_strlen(lex->next->content) == 1)
	{
		printf("%d: command not found\n", error_code);
		error_code = 127;
		return ;
	}
}

void	ft_free_oldpwd(char **env)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], "OLDPWD=", 7) == 0)
			env[i] = NULL;
		i++;
	}
}
/*
int	ft_dollar_env(t_lex *lex)
{
	
}*/