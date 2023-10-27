/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 14:07:53 by rgreiner          #+#    #+#             */
/*   Updated: 2023/10/27 04:12:31 by marvin           ###   ########.fr       */
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
