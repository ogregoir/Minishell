/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 18:08:02 by rgreiner          #+#    #+#             */
/*   Updated: 2023/10/12 17:23:11 by marvin           ###   ########.fr       */
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


char **create_env(char **env)
{
	char **envmini;
	int	i;

	i = 0;
	while(env[i])
		i++;
	envmini = malloc(sizeof(char**) * i + 1);
	i = 0;
	
	while(env[i])
	{
		envmini[i] = ft_strdup(env[i]);
		i++;
	}
	ft_free_oldpwd(envmini);
	return(envmini);
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

void	ft_print_dollar(t_lex *lex, t_global *data)
{
	int		l;
	
	l = 1;
	if (lex->content[0] == '?' && lex->content[1] != '\0')
	{
		printf("%d", data->error_code);
		while (lex->content[l] != '\0')
		{
			if (lex->content[l] == '$' && lex->content[l + 1] == '?')
			{
				printf("%d", data->error_code);
				l += 2;
			}
			else
			{
				printf("%c", lex->content[l]);
				l++;
			}
		}
		printf("\n");
	}				
}

int	ft_dollar_env(t_lex *lex, t_global *data)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = ft_strlen(lex->content);
	str = NULL;
	if(ft_strncmp(lex->content, "?", 1) == 0)
	{
		if (j == 1)
		{
			printf("%d\n", data->error_code);
			return(0);
		}
		else
		{
			ft_print_dollar(lex, data);
		}	
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
	while (data->envmini[i])
	{
		if (ft_strncmp(data->envmini[i], lex->content, j) == 0)
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

