/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 18:08:02 by rgreiner          #+#    #+#             */
/*   Updated: 2023/10/27 14:30:29 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_dollar(t_lex *lex, t_global *data)
{
	if (!lex->next)
	{
		printf("$: command not found\n");
		return ;
	}
	if (ft_strncmp(lex->next->content, "?", 1) == 0
		&& ft_strlen(lex->next->content) == 1)
	{
		printf("%d: command not found\n", data->error_code);
		data->error_code = 127;
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

char	**create_env(char **env, t_global *data)
{
	char	**envmini;
	int		i;

	i = 0;
	while (env[i])
		i++;
	data->size_env = i;
	envmini = malloc(sizeof(char **) * i + 1);
	i = 0;
	while (env[i])
	{
		envmini[i] = ft_strdup(env[i]);
		i++;
	}
	ft_free_oldpwd(envmini);
	return (envmini);
}

int	ft_dollar_access(char *str)
{
	char	*s;

	s = NULL;
	if (access(str, F_OK | R_OK) == 0 && str != NULL)
	{
		s = ft_strjoin("minishell: ", str);
		printf("%s\n", ft_strjoin(s, ": Is a directory"));
		return (126);
	}
	else if (str[0] == '/')
	{
		s = ft_strjoin("-minishell: ", str);
		printf("%s\n", ft_strjoin(s, ": No such file or directory"));
	}
	else
		printf("%s\n", ft_strjoin(str, ": command not found"));
	return (127);
}
