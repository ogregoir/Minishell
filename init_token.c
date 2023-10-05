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

#include "minishell.h"


void	ft_print_tok(t_global *data)
{
	int	i;

	i = 0;
	while (i != 9)
	{
		printf("tok %d, %s\n", i, data->token[i].token);
		printf("tok %d, %d\n", i, data->token[i].len);
		printf("tok %d, %d\n", i, data->token[i].type);
		i++;
	}
}

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

void	ft_init_token(t_global *data)
{
	int	j;

	j = 0;
	data->token = malloc(sizeof(t_structtok));
	data->error_code = 0;
	data->envmini = NULL;
	data->fd = NULL;
	data->pid = NULL;
	while (j != 9)
	{
		if (j == 0 || j == 1 || j == 2 || j == 3)
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
		else
			ft_init_token2(data, j);
		j++;
	}
}
