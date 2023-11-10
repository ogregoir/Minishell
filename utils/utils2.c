/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgreiner <rgreiner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 14:07:53 by rgreiner          #+#    #+#             */
/*   Updated: 2023/11/10 16:04:40 by rgreiner         ###   ########.fr       */
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

char    **create_env(char **env, t_global *data)
{
    char    **envmini;
    int        i;
    int        j;

    i = 0;
    while (env[i])
        i++;
    data->size_env = i;
    envmini = malloc(sizeof(char *) * (i + 1));
    j = 0;
    i = 0;
    while (j < data->size_env)
    {
        if (ft_strncmp(env[j], "OLDPWD=", 7) != 0)
        {
            envmini[i] = ft_strdup(env[j]);
            i++;
            j++;
        }
        else
            j++;
    }
    envmini[i] = NULL;
    return (envmini);
}
