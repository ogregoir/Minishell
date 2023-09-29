/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgreiner <rgreiner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 14:17:35 by rgreiner          #+#    #+#             */
/*   Updated: 2023/09/29 09:10:47 by rgreiner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_detect_quotes(char *line)
{
	int i;
	int	nbr_s;
	int nbr_d;

	i = 0;
	nbr_s = 0;
	nbr_d = 0;
	while(line[i])
	{
		if(line[i] == 34)
			nbr_d++;
		if(line[i] == 39)
			nbr_s++;
		i++;
	}
	if(nbr_d == 0 && nbr_s == 0)
		return (0);
	nbr_s = nbr_s % 2;
	nbr_d = nbr_d % 2;
	if(nbr_d == 0 && nbr_s == 0)
		return (1);
	printf("Invalid numbers of quotes\n");
	exit(1);
	return(0);
}

int	ft_check_nbr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

void	ft_free_split(char **split)
{
	int		i;
	char	*tmp;

	i = 0;
	while (split[i] != NULL)
	{
		tmp = split[i];
		i++;
		free(tmp);
	}
	free(split);
	split = NULL;
}

t_lex	*ft_lstnew(char *content, t_token_type i)
{
	t_lex	*list;

	if(content[0] == '\0')
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
	
	if(content[0] == '\0')
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

void	ft_error(char *arg)
{
	//ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putendl_fd(": command not found", STDERR_FILENO);
	exit(1);
}

char	*ft_strdup2(const char *src, int n)
{
	char	*tab;
	int		i;

	i = 0;
	tab = malloc(sizeof(char *) * (ft_strlen(src) -n + 1));
	while (src[i])
	{
		tab[i] = src[n];
		i++;
		n++;
	}
	tab[i] = '\0';
	return (tab);
}