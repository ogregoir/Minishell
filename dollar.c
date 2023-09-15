/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 18:08:02 by rgreiner          #+#    #+#             */
/*   Updated: 2023/09/15 03:25:45 by marvin           ###   ########.fr       */
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

void	ft_oldpwd(char **env, char **line)
{
	int		i;
	int		l;

	l = 0;
	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], "OLDPWD=", 7) != 0)
		{
			env[i] = ft_strjoin("OLDPWD=", getcwd(line[1], 100));
			while(env[l] != NULL)
			{
				if (env[l] != env[i] && ft_strncmp(env[l], "OLDPWD=", 7) == 0)
					env[l] = NULL;
				l++;
			}
			return ;
		}
		else if (ft_strncmp(env[i], "OLDPWD=", 7) == 0)
		{
			free(env[i]);
			env[i] = ft_strjoin("OLDPWD=", getcwd(line[i], 100));
			return ;
		}
		i++;
	}
}