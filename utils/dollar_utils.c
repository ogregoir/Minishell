/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 01:33:10 by marvin            #+#    #+#             */
/*   Updated: 2023/10/27 01:33:10 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_convert_dollar(char *input, char *err_code, int size, t_global *data)
{
	char	*dollar;
	char	*cpy;
	char	*env;
	char	*name;
	char	*end;
	char	*line;
	char	*linepos;
	int		len;

	cpy = ft_strdup(input);
	len = ft_len_malloc(cpy, err_code, size, data);
	line = malloc(sizeof(char *) * (len + 1));
	linepos = line;
	while (1)
	{
		dollar = ft_strnstr(input, "$", ft_strlen(input));
		if (dollar == NULL)
			break ;	
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
	linepos[len - 1] = '\0';
	free(err_code);
	free(cpy);
	return (line);
}

t_lex	*dollar_lexer(t_lex *tofree, t_global *data)
{
	char	*tmp2;
	t_lex	*tmp;
	t_lex	*lex;

	tmp = NULL;
	lex = tofree;
	while (lex)
	{
		if (lex->type == 0)
		{
			if (ft_strlen(lex->content) == 1)
			{
				if (!tmp)
					tmp = ft_lstnew(ft_strdup("$"), 8);
				else
					addcontent(tmp, ft_strdup("$"), 8);
			}
			else
			{
				tmp2 = ft_convert_dollar(lex->content, ft_itoa(data->error_code), 0, data);
				if (!tmp)
					tmp = ft_lstnew(tmp2, 8);
				else
					addcontent(tmp, tmp2, 8);
				if(lex->next && lex->next->next)
					lex = lex->next;
			}
		}
		else
		{
			tmp2 = ft_strdup(lex->content);
			if(!tmp)
				tmp = ft_lstnew(tmp2, lex->type);
			else
				addcontent(tmp, tmp2, lex->type);
		}
		lex = lex->next;
	}
	ft_free_list(tofree);
	return (tmp);
}
