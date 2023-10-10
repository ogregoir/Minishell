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
	if (i == 0)
		newbuf = ft_substr(buf, 0, 1);
	else
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

int	ft_access_cd(t_global *data, char *buf, char **line, char *oldbuf)
{
	if (access(buf, F_OK | R_OK) == 0 && buf != NULL)
	{
		ft_moove_env(oldbuf, "OLDPWD=", data);
		ft_moove_env(buf, "PWD=", data);
		if (line[1] != NULL && line[1][0] == 45 && line[1][1] == '\0')
			printf("%s\n", buf);
		chdir(buf);
		free(buf);
		return (0);
	}
	else
	{
		printf("-minishell: cd: %s: No such file or directory\n", line[1]);
		return (1);
	}
}

int	ft_oldbuf(t_global *data, char **line)
{
	int		i;

	i = 0;
	if (line[1][2] == '-')
	{
		printf("-minishell: %s: invalid option\n", line[1]);
		return (2);
	}
	else if (line[1][0] == '-')
	{
		if (line[1][1] == '-')
			return (0);
		while (data->envmini[i] != NULL)
		{
			if (ft_strncmp(data->envmini[i], "OLDPWD=", 7) != 0)
				i++;
			else
				return (0);
		}
		printf("-minishell: cd: OLDPWD not set\n");
		return (1);
	}
	return (0);
}

int	ft_cd(t_global *data, char **line)
{
	char	*buf;
	int		j;
	char	*oldbuf;

	j = 0;
	buf = NULL;
	buf = getcwd(buf, 100);
	oldbuf = ft_strdup(buf);
	if (line[2] != NULL)
		return (error_arguments());
	else if (line[1] == NULL || line[1][0] == 126)
		buf = ft_strdup(getenv("HOME"));
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
	else if (line[1][0] == 40 || line[1][0] == 41)
		return (error_parentheses(line));
	else
		return (no_such_directory(line));
	j = ft_access_cd(data, buf, line, oldbuf);
	return (j);
}
