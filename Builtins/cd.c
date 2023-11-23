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
	while (buf[i] != 47)
		i--;
	if (i == 0)
		newbuf = ft_substr(buf, 0, 1);
	else
		newbuf = ft_substr(buf, 0, i);
	free (buf);
	return (newbuf);
}

char	*ft_forward(char *buf, char *line)
{
	char	*temp;
	char	*newbuf;
	char	*bis;

	bis = NULL;
	temp = ft_strjoin(buf, "/");
	if (line[ft_strlen(line) - 1] == 47)
	{
		bis = ft_substr(line, 0, (ft_strlen(line) - 1));
		newbuf = ft_strjoin(temp, bis);
	}
	else
		newbuf = ft_strjoin(temp, line);
	free (temp);
	if (bis)
		free (bis);
	free (buf);
	return (newbuf);
}

int	ft_verif_cd(t_lex *lex, t_global *data, char *oldbuf)
{
	char	*newbuf;

	newbuf = NULL;
	if (!lex->next || lex->next->content[0] == 126)
	{
		if (ft_variable_exist(data, "HOME") == 1)
			return (1);
		else
		{
			newbuf = getenv("HOME");
			ft_moove_env(newbuf, "PWD=", data);
			ft_moove_env(oldbuf, "OLDPWD=", data);
			chdir(newbuf);
			return (2);
		}
	}
	lex = lex->next;
	if (lex->next)
		return (2);
	return (0);
}

char	*ft_back2(t_lex *lex, char *buf)
{
	char	*new_buf;

	new_buf = NULL;
	if (ft_strlen(lex->content) == 2)
	{
		new_buf = ft_back(buf);
		return (new_buf);
	}
	else if (lex->content[2] == 47)
	{
		free(buf);
		new_buf = ft_strdup(lex->content);
		return (new_buf);
	}
	return (buf);
}

int	ft_cd(t_global *data, t_lex *lex)
{
	char	*buf;
	char	*oldbuf;

	buf = NULL;
	if (ft_verif2(data, lex) == 0 || ft_verif2(data, lex) == 1)
	{
		if (ft_verif2(data, lex) == 1)
			ft_error("cd: HOME not set", "", "", 1);
		return (ft_verif2(data, lex));
	}
	if (lex->next->content[0] == '.' && ft_strlen(lex->next->content) == 1)
		return (0);
	buf = getcwd(buf, 100);
	oldbuf = ft_strdup(buf);
	lex = lex->next;
	if (ft_strncmp(lex->content, "..", 2) == 0)
		buf = ft_back2(lex, buf);
	else if (lex->content[0] == 47)
	{
		free (buf);
		buf = ft_substr(lex->content, 0, ft_strlen(lex->content));
	}
	else if (ft_isalnum(lex->content[0]) != 0)
		buf = ft_forward(buf, lex->content);
	return (ft_access_cd(data, buf, lex->content, oldbuf));
}
