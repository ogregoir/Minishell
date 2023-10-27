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
	if (j == 4 || j == 5)
	{
		data->token[j].len = 2;
		data->token[j].type = j;
		if (j == 4)
			data->token[4].token = ft_strdup("<<");
		else
			data->token[5].token = ft_strdup(">>");
	}
	else if (j == 6 || j == 7 || j == 8)
	{
		data->token[j].token = malloc(sizeof(char *) * 1);
		data->token[j].len = 1;
		data->token[j].type = j;
		if (j == 6)
			data->token[6].token = "'";
		else if (j == 7)
			data->token[7].token = "\"";
		else
			data->token[8].token = NULL;
	}
}

void	ft_init_token3(t_global *data, int j)
{
	data->token[j].token = malloc(sizeof(char *) * 1);
	data->token[j].len = 1;
	data->token[j].type = j;
	if (j == 0)
		data->token[0].token = "$";
	else if (j == 1)
		data->token[1].token = "|";
	else if (j == 2)
		data->token[2].token = "<";
	else if (j == 3)
		data->token[3].token = ">";
}

void	ft_init_token(t_global *data)
{
	int	j;

	j = 0;
	data->token = malloc(sizeof(t_listtest));
	data->error_code = 0;
	data->envmini = NULL;
	data->fd = NULL;
	data->pid = NULL;
	while (j != 9)
	{
		if (j == 0 || j == 1 || j == 2 || j == 3)
			ft_init_token3(data, j);
		else
			ft_init_token2(data, j);
		j++;
	}
}

t_lex	*check_dollar(t_lex *lex, t_global *data, char *s)
{
	if (ft_strncmp(s, "?", 1) == 0 && ft_strlen(s) == 1)
	{
		if (!lex)
			lex = ft_lstnew(ft_itoa(data->error_code), 8);
		else
			addcontent(lex, ft_itoa(data->error_code), 8);
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
		lex = ft_check_type(line[i], lex, 0, 0, data);
		i++;
	}
	return (lex);
}
