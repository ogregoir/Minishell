/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgreiner <rgreiner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 14:07:53 by rgreiner          #+#    #+#             */
/*   Updated: 2023/10/24 16:27:36 by rgreiner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *ft_get_env(char *str, char **env)
{
	char *ret;
	int i;
	int len;

	len = ft_strlen(str);
	i = 0;
	ret = NULL;
	if(len == 0)
		return(NULL);
	while(env[i])
	{
		if(ft_strncmp(str, env[i], len) == 0)
			ret = ft_strdup(env[i] + (len +1));
		i++;
	}
	return (ret);
	
}

void free_list(t_lex *lex)
{
	while (lex->next)
	{
		free(lex->content);
		lex = lex->next;
	}
}

int ft_isspace(int i)
{
	if (i == 32)
		return (1);
	else
		return (0);
}

char *ft_last_ele(t_lex *lex)
{
	char *ret;
	t_lex *tmp;

	tmp = lex;
	while (tmp->next)
		tmp = tmp->next;
	ret = ft_strdup(tmp->content);
	return (ret);
}

int ft_len_malloc(char *input, char *err_code, int size, t_global *data)
{
	int len;
	char *dollar;
	char *end;
	char *name;
	char *env;
	while (1)
	{
		dollar = ft_strnstr(input, "$", ft_strlen(input));
		if (dollar == NULL)
			break;
		size = size + dollar - input;
		input = dollar + 1;
		if (input[0] == '?')
		{
			size = size + ft_strlen(err_code);
			input++;
		}
		else if (input[0] != '\0')
		{
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
		}
	}
	size = size + ft_strlen(input);
	return (size);
}

char *ft_strncpy(char *str, char *src, int i)
{
	char *dest;
	dest = str;

	while (i > 0 && *src != '\0')
	{
		*dest = *src;
		dest++;
		src++;
		i--;
	}

	while (i > 0)
	{
		*dest = '\0';
		dest++;
		i--;
	}
	return (str);
}

char *ft_convert_dollar(char *input, char *err_code, int size, t_global *data)
{
	char *dollar;
	char *cpy;
	char *env;
	char *name;
	char *end;
	char *line;
	char *linepos;
	int len;

	cpy = ft_strdup(input);
	len = ft_len_malloc(cpy, err_code, size, data);
	line = malloc(sizeof(char *) * (len + 1));
	linepos = line;
	while (1)
	{
		dollar = ft_strnstr(input, "$", ft_strlen(input));
		if (dollar == NULL)
			break;
		ft_strncpy(linepos, input, (dollar - input));
		linepos += dollar - input;
		input = dollar + 1;
		if (input[0] == '?')
		{
			ft_strncpy(linepos, err_code, ft_strlen(err_code));
			linepos += ft_strlen(err_code);
			input++;
		}
		else if (input[0] != '\0')
		{
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
				{
					ft_strncpy(linepos, env, ft_strlen(env));
					linepos += ft_strlen(env);
				}
				else
				{
					ft_strncpy(linepos, name, ft_strlen(name));
					linepos += len;
				}
				input = end;
			}
			else
			{
				*linepos = '$';
				linepos += 1;
			}
		}
	}
	ft_strncpy(linepos, input, ft_strlen(input));
	return (line);
}

t_lex *dollar_lexer(t_lex *lex, t_global *data)
{
	char *tmp2;
	t_lex *tmp;

	tmp = NULL;
	while (lex)
	{
		if (lex->type == 0)
		{
			if (ft_strlen(lex->content) == 1)
			{
				if (!tmp)
					tmp = ft_lstnew("$", 8);
				else
					addcontent(tmp, "$", 8);
			}
			else
			{
				tmp2 = ft_convert_dollar(lex->content, ft_itoa(data->error_code), 0, data);
				if (!tmp)
					tmp = ft_lstnew(tmp2, 8);
				else
					addcontent(tmp, tmp2, 8);
			}
		}
		else if (!tmp)
			tmp = ft_lstnew(lex->content, lex->type);
		else
			addcontent(tmp, lex->content, lex->type);
		lex = lex->next;
	}
	return (tmp);
}