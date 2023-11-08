/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_liste_chainee.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 01:04:43 by marvin            #+#    #+#             */
/*   Updated: 2023/10/27 01:04:43 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_lex	*ft_lstnew(char *content, t_token_type i)
{
	t_lex	*list;

	if (content[0] == '\0')
		return (0);
	list = malloc(sizeof(t_lex));
	if (!list)
		return (0);
	list -> content = content;
	list -> type = i;
	list -> next = NULL;
	return (list);
}

void	addcontent(t_lex *list, char *content, t_token_type i)
{
	t_lex	*new;
	t_lex	*temp;

	if (content[0] == '\0')
		return ;
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

int	ft_isspace(int i)
{
	if (i == 32)
		return (1);
	else
		return (0);
}

char	*ft_get_env(char *str, char **env)
{
	char	*ret;
	int		i;
	int		len;

	len = ft_strlen(str);
	i = 0;
	ret = NULL;
	if (len == 0)
		return (NULL);
	while (env[i])
	{
		if (ft_strncmp(str, env[i], len) == 0)
			ret = ft_strdup(env[i] + (len +1));
		i++;
	}
	return (ret);
}

char	**ft_free_char(char **str)
{
	int	i;

	i = 0;
	if (!str || str[i] == NULL)
		return ;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	return (str);
}