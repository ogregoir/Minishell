/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 18:59:35 by marvin            #+#    #+#             */
/*   Updated: 2023/09/06 18:59:35 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_export2(char **env, char **line, int i)
{
	int	l;
	int	j;

	l = 0;
	j = 0;
	while (env[l] != NULL)
		l++;
	while (line[i][j])
	{
		if (line[i][j] == '=')
		{
			env[l] = ft_substr(line[i], 0, ft_strlen(line[i]));
			env[l + 1] = NULL;
			return (0);
		}
		j++;
	}
	return (0);
}

int	ft_already_exists(char **line, char **env)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (line[1][i] != '=')
		i++;
	while (env[j] != NULL)
	{
		if (ft_strncmp(line[1], env[j], i) == 0)
		{
			env[j] = NULL;
			env[j] = ft_strdup(line[1]);
			return (0);
		}
		j++;
	}
	return (0);
}

int	ft_export(char **line, char **env)
{
	int		i;
	int		j;

	i = 1;
	j = 0;
	if (line[1] == NULL)
		return (0);
	if (line[i] != NULL)
	{
		while (line[i] != NULL)
		{
			if (ft_already_exists(line, env) != 0)
				j = ft_export2(env, line, i);
			else
				j = ft_already_exists(line, env);
			i++;
		}
	}
	return (j);
}

int	ft_unset(char **line, char **env)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (line[1] == NULL)
		return (j);
	while (env[i])
	{
		if (ft_strncmp(line[1], env[i], ft_strlen(line[1])) == 0)
		{
			free(env[i]);
			env[i] = NULL;
			return (j);
		}
		i++;
	}
	return (j);
}


char	*ft_oldpwd(char **env, char **line)
{
	int		i;
	char	*buf;

	i = 0;
	buf = NULL;
	if (line[1][1] == '-')
	{
		buf = ft_strdup(getenv("HOME"));
		return (buf);
	}
	else
	{
		while (env[i] != NULL)
		{
			if (ft_strncmp(env[i], "OLDPWD=", 7) == 0)
				buf = ft_substr(env[i], 7, ft_strlen(env[i]));
			i++;
		}
		return (buf);
	}
	return (buf);
}

void	ft_oldpwd2(char **env, char *oldbuf)
{
	int		i;

	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], "OLDPWD=", 7) == 0)
		{	
			free(env[i]);
			env[i] = ft_strjoin("OLDPWD=", oldbuf);
			env[i + 1] = NULL;
			return ;
		}
		i++;
	}
	if (env[i] == NULL)
	{
		env[i] = ft_strjoin("OLDPWD=", oldbuf);
		env[i + 1] = NULL;
	}
}