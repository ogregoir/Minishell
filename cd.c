/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 03:39:56 by marvin            #+#    #+#             */
/*   Updated: 2023/08/29 03:39:56 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_back(char *buf)
{
	int		i;
	char	*newbuf;

	i = ft_strlen(buf);
	newbuf = malloc((ft_strlen(buf)) - 1);
	while (buf[i] != 47)
		i--;
	newbuf = ft_substr(buf, 0, i);
	return (newbuf);
}

char	*ft_forward(char *buf, char **line)
{
	char	*temp;
	char	*newbuf;
	char	*bis;

	temp = ft_strjoin(buf, "/");
	if (line[1][ft_strlen(line[1]) - 1] == 47)
	{
		bis = ft_substr(line[1], 0, (ft_strlen(line[1]) - 1));
		newbuf = ft_strjoin(temp, bis);
	}
	else
		newbuf = ft_strjoin(temp, line[1]);
	return (newbuf);
}

int	ft_access_cd(char **env, char *buf, char **line, int j)
{
	(void)env;
	if (access(buf, F_OK | R_OK) == 0 && buf != NULL)
	{
		//ft_oldpwd(env, line);
		if (line[1] != NULL && line[1][0] == 45)
			printf("%s\n", buf);
		chdir(buf);
		return (j);
	}
	else if (line[1][0] == 45)
	{
		printf("%s\n", buf);
		return (1);
	}
	else
	{
		printf("minishell: cd: %s: No such file or directory\n", buf);
		return (1);
	}
	free(buf);
}

char	*ft_oldbuf(char **env)
{
	int		i;
	char	*buf;
	char	*newbuf;

	i = 0;
	buf = NULL;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], "OLDPWD=", 7) == 0)
		{
			buf = ft_substr(env[i], 7, ft_strlen(env[i]));
			return (buf);
		}
		i++;
	}
	if (buf == NULL)
		newbuf = ft_strdup("-minishell: cd: OLDPWD not set");
	return (newbuf);
}

int	ft_cd(char **env, char **line)
{
	char	*buf;
	int		j;

	j = 0;
	buf = NULL;
	buf = getcwd(buf, 100);
	if (line[1] == NULL || line[1][0] == 126)
		buf = getenv("HOME");
	else if (ft_strncmp(line[1], "..", ft_strlen(line[1])) == 0)
	{
		if (ft_strlen(line[1]) == 1)
			return (0);
		else
			buf = ft_back(buf);
	}
	else if (line[1][0] == 47)
		buf = ft_substr(line[1], 0, ft_strlen(line[1]));
	else if (ft_isalnum(line[1][0]) != 0)
		buf = ft_forward(buf, line);
	else if (line[1][0] == 45)
	{
		if (line[1][1] != '\0')
		{
			printf("-minishell: %s: invalid option\n", line[1]);
			return (2);
		}
		else
			buf = ft_oldbuf(env);
	}
	else
	{
		printf ("-minishell: cd: %s: No such file or directory\n", line[1]);
		return (1);
	}
	j = ft_access_cd(env, buf, line, j);
	return (j);
}
