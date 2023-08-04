/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogregoir <ogregoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 17:35:07 by rgreiner          #+#    #+#             */
/*   Updated: 2023/07/10 15:32:01 by ogregoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_search_quote(char *line, char c)
{
	int		i;
	char	*str;
	int		j;

	i = 0;
	while (line[i])
	{
		if (line[i] == c)
		{
			j = i;
			while (line[i])
			{
				i++;
				if (line[i] == c)
				{
					str = ft_substr(line, j+1, i-1);
					return (str);
				}
			}
		}
		else
			i++;
	}
	return(line);
}

static int	ft_malloc_quote(char *line)
{
	int		j;
	int		i;
	
	j = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == 34)
			j++;
		else if (line[i] == 39)
			j++;
		else if (line[i] == ' ')
			j++;
		i++;
	}
	return (j);
}

char	*ft_check_quote(char *line, int i)
{
	char	*str;

	if (line[i] == 34)
	{			
		str = ft_search_quote(line, 34);
		return (str);
	}
	else if (line[i] == 39)
	{
		str = ft_search_quote(line, 39);
		return (str);
	}
	else
	{
		while (line[i])
		{
			if (line[i] == ' ' || line[i] == 34 || line [i] == 39)
			{
				str = ft_substr(line, 0, i);
				return (str);
			}
		i++;
		}
	}
	return (line);
}

char	**ft_quote(char *line)
{
	char	**str;
	int		i;
	int		j;

	i = 0;
	j = ft_malloc_quote(line);
	str = malloc(sizeof(char *) * j + 1);
	j = 0;
	while(line[i] != '\0')
	{	
		if (line[i] == ' ')
		{
			i++;
			str[j] = ft_calloc(1, 1);
			j++;
			line = ft_substr(line, i, ft_strlen(line));
			i = 0;
		}
		if (line[i] == '\0')
			break;
		str[j] = ft_check_quote(line, i);	
		j++;
		if (line[i] == 34 || line[i] == 39)
			i = ft_strlen(str[j - 1]) +2;
		else 
			i = ft_strlen(str[j - 1]);
		line = ft_substr(line, i, ft_strlen(line));
		i = 0;
	}
	str[j] = NULL;
	return (str);
}