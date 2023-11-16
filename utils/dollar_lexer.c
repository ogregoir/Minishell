/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_lexer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 16:00:37 by rgreiner          #+#    #+#             */
/*   Updated: 2023/11/16 08:08:35 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_dollar(t_dollar *d, char *input, int size, t_global *data)
{
	d->err_code = ft_itoa(data->error_code);
	d->cpy = ft_strdup(input);
	d->len = ft_len_malloc(d->cpy, d->err_code, size, data);
	d->line = malloc(sizeof(char *) * (d->len + 1));
	d->linepos = d->line;
	d->dollar = NULL;
	d->env = NULL;
	d->name = NULL;
	d->end = NULL;
}

void	free_dollar(t_dollar *d)
{
	if (d->err_code)
		free(d->err_code);
	if (d->cpy)
		free(d->cpy);
	if (d->env)
		free(d->env);
	if (d->name)
		free(d->name);
	if (d->line)
		free(d->line);
	if (d->dollar)
		free(d->dollar);
	free(d);
}

char	*ft_dollar_err(t_dollar *d, char *input)
{
	ft_strncpy(d->linepos, d->err_code, ft_strlen(d->err_code));
	input++;
	if(input[0] != '\0')
		d->linepos += ft_strlen(d->err_code);
	return (input);
}

char	*ft_convert_dollar2(t_dollar *d, char *input, t_global *data)
{
	d->end = input;
	while (*d->end && (ft_isalnum(*d->end) || *d->end == '_'))
		d->end++;
	if (input != d->end)
	{
		d->len = d->end - input;
		d->name = ft_strndup(input, d->len);
		d->name[d->len] = '\0';
		d->env = ft_get_env(d->name, data->envmini);
		if (d->env != NULL)
		{
			ft_strncpy(d->linepos, d->env, ft_strlen(d->env));
			d->linepos += ft_strlen(d->env);
		}
		else
			d->linepos += d->len;
		input = d->end;
	}
	else
	{
		*d->linepos = '$';
		d->linepos += 1;
	}
	return(input);
}

char	*ft_convert_dollar(char *input, int size, t_global *data)
{
    t_dollar *d;
	char	*ret;

	d = malloc(sizeof(t_dollar));
    init_dollar(d, input, size, data);
	while (1)
	{
		d->dollar = ft_strnstr(input, "$", ft_strlen(input));
		if (d->dollar == NULL)
			break ;	
		ft_strncpy(d->linepos, input, (d->dollar - input));
		d->linepos += d->dollar - input;
		input = d->dollar + 1;
		if (input[0] == '?')
			input = ft_dollar_err(d, input);
		else if (input[0] != '\0')
			input = ft_convert_dollar2(d, input, data);
	}
	ft_strncpy(d->linepos, input, ft_strlen(input));
	d->linepos[d->len] = '\0';
	ret = ft_strdup(d->line);
	free_dollar(d);
	return (ret);
}
