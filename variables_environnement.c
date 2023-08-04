/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables_environnement.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogregoir <ogregoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 14:40:01 by ogregoir          #+#    #+#             */
/*   Updated: 2023/07/01 18:19:30 by ogregoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	len_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == 61)
			return (i);
		i++;
	}
	return (i);
}

static void	acces_venv(char *str, char *line)
{
	if (!ft_strchr(line, '='))
	{
		if (access(str, F_OK) == 0)
			printf(": is a directory");
		else
			printf(": No such file or directory");
	}
	else
		printf(": No such file or directory");
}

void	ft_variables_env(char *line)
{
	char	*str;
	char	**n_line;
	int		i;
	int		j;

	str = NULL;
	j = len_line(line);
	i = 0;
	if (line[i] == '$')
	{
		i++;
		str = getenv(&line[i]);
		printf("minishell: %s", str);
		if (line[j] == '=')
		{
			printf("%c", '=');
			if (line[j +1] != '\0')
			{
				n_line = ft_split(line, '=');
				printf("%s", n_line[1]);
			}
		}
		acces_venv(str, line);
		printf("\n");
	}
}
