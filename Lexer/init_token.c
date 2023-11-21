/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 03:03:03 by marvin            #+#    #+#             */
/*   Updated: 2023/10/01 03:03:03 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_init_token2(t_global *data, int j)
{
	if (j == 0 || j == 1)
	{
		data->token[j].len = 2;
		if (j == 0)
		{
			data->token[j].token = ft_strdup("<<");
			data->token[j].type = 4;
		}
		else
		{
			data->token[j].token = ft_strdup(">>");
			data->token[j].type = 5;
		}
	}
	else if (j == 6 || j == 7 || j == 8)
	{
		data->token[j].len = 1;
		data->token[j].type = j;
		if (j == 6)
			data->token[6].token = ft_strdup("'");
		else if (j == 7)
			data->token[7].token = ft_strdup("\"");
		else
			data->token[8].token = NULL;
	}
}

void	ft_init_token3(t_global *data, int j)
{
	data->token[j].len = 1;
	if (j == 2)
	{
		data->token[j].token = ft_strdup("$");
		data->token[j].type = 0;
	}
	else if (j == 3)
	{
		data->token[j].token = ft_strdup("|");
		data->token[j].type = 1;
	}
	else if (j == 4)
	{
		data->token[j].token = ft_strdup("<");
		data->token[j].type = 2;
	}
	else if (j == 5)
	{
		data->token[j].token = ft_strdup(">");
		data->token[j].type = 3;
	}
}

void	ft_init_token(t_global *data, char **env)
{
	int	j;

	j = 0;
	data->token = malloc(sizeof(t_listtest) * 9);
	data->envmini = NULL;
	data->fd = NULL;
	data->pid = NULL;
	data->envmini = create_env(env, data);
	data->env_exp = malloc(sizeof(char *) * 1);
	data->env_exp[0] = NULL;
	while (j != 9)
	{
		if (j == 2 || j == 3 || j == 4 || j == 5)
			ft_init_token3(data, j);
		else
			ft_init_token2(data, j);
		j++;
	}
}

t_lex	*check_dollar(t_lex *lex, char *s)
{
	if (ft_strncmp(s, "?", 1) == 0 && ft_strlen(s) == 1)
	{
		if (!lex)
			lex = ft_lstnew(ft_itoa(g_error), 8);
		else
			addcontent(lex, ft_itoa(g_error), 8);
	}
	return (lex);
}

t_lex	*ft_lexer(char **line, t_lex *lex, t_global *data)
{
	int	i;

	i = 0;
	lex = NULL;
	while (line[i])
	{
		lex = ft_check_type(line[i], lex, 0, data);
		free(line[i]);
		line[i] = NULL;
		i++;
	}
	return (lex);
}
