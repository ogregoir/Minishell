/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgreiner <rgreiner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 18:08:02 by rgreiner          #+#    #+#             */
/*   Updated: 2023/09/30 16:54:20 by rgreiner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_dollar(t_lex *lex)
{
	if (!lex->next)
	{
		printf("$: command not found\n");
		return ;
	}
	if (ft_strncmp(lex->next->content, "?", 1) == 0 
		&& ft_strlen(lex->next->content) == 1)
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

int	ft_dollar_env(t_lex *lex, char **env)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = ft_strlen(lex->content);
	str = NULL;
	if(j == 1 && ft_strncmp(lex->content, "?", 1) == 0)
	{
			printf("%d\n", error_code);
			return(0);
	}
	if(j == 1 && ft_strncmp(lex->content, "$", 1) == 0)
		{
			printf("$: command not found\n");
			return(127);
		}
	if (ft_strchr(lex->content, 48) != 0)
	{
		printf("Command '-minishell' not found\n");
		return (127);
	}
	while (env[i])
	{
		if (ft_strncmp(env[i], lex->content, j) == 0)
			str = getenv(lex->content);
		i++;
	}
	if (str == NULL)
		return (0);
	i = 0;
	while (str[i] != 32)
		i++;
	str = ft_substr(str, 0, i);
	return (ft_dollar_access(str));
}
