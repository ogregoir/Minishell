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

#include "../minishell.h"

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

char	*ft_forward(char *buf, char *line)
{
	char	*temp;
	char	*newbuf;
	char	*bis;

	temp = ft_strjoin(buf, "/");
	if (line[ft_strlen(line) - 1] == 47)
	{
		bis = ft_substr(line, 0, (ft_strlen(line) - 1));
		newbuf = ft_strjoin(temp, bis);
	}
	else
		newbuf = ft_strjoin(temp, line);
	return (newbuf);
}

int	ft_verif_cd(t_lex *lex, t_global *data)
{
	char	*buf;

	buf = NULL;
	if (!lex->next || lex->next->content[0] == 126)
	{
		if (ft_variable_exist(data, "HOME") == 1)
		{
			ft_error("cd: HOME not set", "", "", 1);
			return (1);
		}
		else
		{
			buf = ft_strdup(getenv("HOME"));
			chdir(buf);
			return (2);
		}
	}
	lex = lex->next;
	if (lex->next)
		return (1);
	return (0);
}

int	ft_cd(t_global *data, t_lex *lex)
{
	char	*buf;
	char	*oldbuf;

	buf = NULL;
	buf = getcwd(buf, 100);
	oldbuf = ft_strdup(buf);
	if (ft_verif_cd(lex, data) == 1)
		return (1);
	else if (ft_verif_cd(lex, data) == 2)
		return (0);
	lex = lex->next;
	if (ft_strncmp(lex->content, "..", ft_strlen(lex->content)) == 0)
	{
		if (ft_strlen(lex->content) == 1)
			return (0);
		else
			buf = ft_back(buf);
	}
	else if (lex->content[0] == 47)
		buf = ft_substr(lex->content, 0, ft_strlen(lex->content));
	else if (ft_isalnum(lex->content[0]) != 0)
		buf = ft_forward(buf, lex->content);
	else
	{
		ft_error("cd: ", lex->content, ": No such file or directory\n", 0);
		return (1);
	}
	return (ft_access_cd(data, buf, lex->content, oldbuf));
}
