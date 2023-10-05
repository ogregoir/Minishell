/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 17:35:07 by rgreiner          #+#    #+#             */
/*   Updated: 2023/10/04 20:03:58 by marvin           ###   ########.fr       */
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
					if(line[j + 1] == '$' && c == 39)
								str = ft_substr(line, j + 1, i - 1);
					else
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

t_lex	*ft_quote(char *line, t_lex *lex)
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
			str[j] = ft_strdup(" ");
			if(!lex)
				lex = ft_lstnew(str[j], 8);
			else
				addcontent(lex, str[j], 8);
			
			line = ft_substr(line, i, ft_strlen(line));
			i = 0;
		}
		if (line[i] == '\0')
			break;
		str[j] = ft_check_quote(line, i);
		if (!lex && line[i] == 34 && str[j][0] == '$' && ft_strlen(str[j]) > 1)
			lex = ft_lstnew(str[j] + 1, 0);
		else if(line[i] == 34 && str[j][0] == '$' && ft_strlen(str[j]) > 1)
			addcontent(lex, str[j] + 1, 0);
		else if(line[i] != 34 && line[i] != 39)
			lex = ft_lexer_quotes(str[j], lex, i);
		else if(!lex && str[j])
			lex = ft_lstnew(str[j], 8);
		else if(str[j])
			addcontent(lex, str[j], 8);
		j++;
		if (line[i] == 34 || line[i] == 39)
			i = ft_strlen(str[j - 1]) + 2;
		else 
			i = ft_strlen(str[j - 1]);
		line = ft_substr(line, i, ft_strlen(line));
		if((line[0] == 34 || line[0] == 39) && ft_strlen(line) == 1)
			break;
		i = 0;
	}
	str[j] = NULL;
	return(lex);
}
