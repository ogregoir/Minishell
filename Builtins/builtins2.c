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

#include "../minishell.h"

void	ft_free_exp(char *str, t_global *data)
{
	int	i;

	i = 0;
	while (data->env_exp[i])
	{
		if (ft_strncmp(data->env_exp[i], str, ft_strlen(str)) == 0)
		{
			free (data->env_exp[i]);
			while (data->env_exp[i])
			{
				data->env_exp[i] = data->env_exp[i + 1];
				i++;
			}
			return ;
		}
		i++;
	}
}

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
			while (data->envmini[i])
			{
				data->envmini[i] = data->envmini[i + 1];
				i++;
			}
			return ;
		}
		i++;
	}
	ft_free_exp(str, data);
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
		chdir(buf);
		free(buf);
		free(oldbuf);
		return (0);
	}
	else
	{
		//free(buf);
		free(oldbuf);
		ft_error("cd :", line, ": No such file or directory\n", 0);
		return (1);
	}
}
