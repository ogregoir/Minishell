/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 14:07:53 by rgreiner          #+#    #+#             */
/*   Updated: 2023/11/04 15:10:57 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_len_malloc2(char *input, int size, t_global *data)
{
	char	*name;
	char	*env;
	char	*end;
	int		len;

	end = input;
	while (*end && (ft_isalnum(*end) || *end == '_'))
		end++;
	if (input != end)
	{
		len = end - input;
		name = ft_strndup(input, len);
		name[len] = '\0';
		env = ft_get_env(name, data->envmini);
		if (env != NULL)
			size = size + ft_strlen(env);
		else
			size = size + len;
		input = end;
		free(name);
	}
	else
		size = size + 1;
	return (size);
}

int	ft_len_malloc(char *input, char *err_code, int size, t_global *data)
{
	char	*dollar;

	while (1)
	{
		dollar = ft_strnstr(input, "$", ft_strlen(input));
		if (dollar == NULL)
			break ;
		size = size + dollar - input;
		input = dollar + 1;
		if (input[0] == '?')
		{
			size = size + ft_strlen(err_code);
			input++;
		}
		else if (input[0] != '\0')
			size = ft_len_malloc2(input, size, data);
	}
	size = size + ft_strlen(input);
	return (size);
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
