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

void	ft_unset2(char *str, t_global *data)
{
	int	i;

	i = 0;
	if (str == NULL)
		return ;
	while (data->envmini[i])
	{
		if (ft_strncmp(data->envmini[i], str, ft_strlen(str)) == 0)
		{
			free (data->envmini[i]);
			data->envmini[i] = NULL;
		}
		i++;
	}
	i = 0;
	while (data->env_exp[i])
	{
		if (ft_strncmp(data->env_exp[i], str, ft_strlen(str)) == 0)
		{
			free (data->env_exp[i]);
			data->env_exp[i] = NULL;
		}
		i++;
	}
}

int	ft_unset(t_lex *lex, t_global *data)
{
	while (lex->next != NULL)
	{
		lex = lex->next;
		ft_unset2(lex->content, data);
	}
	return (0);
}

void	ft_moove_env(char *oldbuf, char *str, t_global *data)
{
	int			i;

	i = 0;
	while (data->envmini[i] != NULL)
	{
		if (ft_strncmp(data->envmini[i], str, 7) == 0)
		{
			free(data->envmini[i]);
			data->envmini[i] = ft_strjoin(str, oldbuf);
			data->envmini[i + 1] = NULL;
			return ;
		}
		i++;
	}
	if (data->envmini[i] == NULL)
	{
		data->envmini[i] = ft_strjoin(str, oldbuf);
		data->envmini[i + 1] = NULL;
	}
}

int	ft_access_cd(t_global *data, char *buf, char *line, char *oldbuf)
{
	if (access(buf, F_OK | R_OK) == 0 && buf != NULL)
	{
		ft_moove_env(oldbuf, "OLDPWD=", data);
		ft_moove_env(buf, "PWD=", data);
		if (line != NULL && line[0] == 45 && line[1] == '\0')
			printf("%s\n", buf);
		chdir(buf);
		free(buf);
		return (0);
	}
	else
	{
		printf("-minishell: cd: %s: No such file or directory\n", line);
		return (1);
	}
}

int	ft_verif_cd(t_lex *lex, char *buf, char *oldbuf, t_global *data)
{
	int	j;

	j = 0;
	if (!lex->next || lex->next->content[0] == 126)
	{
		buf = ft_strdup(getenv("HOME"));
		j = ft_access_cd(data, buf, lex->content, oldbuf);
		return (j);
	}
	else
		lex = lex->next;
	if (lex->next)
		return (1);
	if (lex->content[0] == 40 || lex->content[0] == 41)
	{
		printf("-minishell: syntax error near unexpected token `%c'\n", lex->content[0]);
		return (2);
	}
	return(0);
}