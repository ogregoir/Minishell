/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgreiner <rgreiner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 14:17:35 by rgreiner          #+#    #+#             */
/*   Updated: 2023/07/03 11:17:29 by rgreiner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_nbr(char **str)
{
	int	i;
	int	j;

	i = 1;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if (str[i][j] < '0' || str[i][j] > '9')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

void	ft_free_split(char **split)
{
	int		i;
	char	*tmp;

	i = 0;
	while (split[i] != '\0')
	{
		tmp = split[i];
		i++;
		free(tmp);
	}
	free(split);
	split = NULL;
}

t_lex	*ft_lstnew(char *content, e_token_type i)
{
	t_lex	*list;

	list = malloc(sizeof(t_lex));
	if (!list)
		return (0);
	list -> content = content;
	list -> type = i;
	list -> next = NULL;
	return (list);
}

void	addcontent(t_lex *list, char *content, e_token_type i)
{
	t_lex	*new;
	t_lex	*temp;

	new = malloc(sizeof(t_lex));
	if (list == NULL || new == NULL)
		return ;
	new->content = content;
	new->type = i;
	new->next = NULL;
	if (list->next != NULL)
	{
		temp = list->next;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}
	else
		list->next = new;
}