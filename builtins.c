/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgreiner <rgreiner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 14:17:58 by rgreiner          #+#    #+#             */
/*   Updated: 2023/07/01 13:43:34 by rgreiner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(char **line)
{
	printf("exit\n");
	if (line[1] == NULL)
		exit (EXIT_SUCCESS);
	if (ft_check_nbr(line) == 1)
	{
		printf("minishell: exit: %s numeric argument required\n", line[1]);
		exit (EXIT_FAILURE);
	}
	else
		exit (ft_atoi(line[1]));
}

void	ft_pwd(void)
{
	char	*buf;
	int		i;

	i = 0;
	buf = NULL;
	buf = getcwd(buf, 100);
	printf("%s\n", buf);
	free(buf);
}

void	ft_env(char **line, char **env)
{
	int	i;

	i = 0;
	if (line[1] != NULL)
	{
		printf("env: %s: No such file or directory\n", line[1]);
		return ;
	}
	while (env[i] != NULL)
	{
		printf("%s\n", env[i]);
		i++;
	}
}

void	ft_echo_2(char **line, int i, int nl)
{
	int	j;

	j = 0;
	while (line[i])
	{
		if (line[i][j] == '$')
			j++;
		if (getenv(line[i] + j) != NULL)
			printf("%s", getenv(line[i] + j));
		else
			printf("%s", line[i]);
		if (line[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (nl == 0)
		printf("\n");
}

void	ft_echo(char **line, int nl)
{
	int	i;
	int	j;

	i = 1;
	j = 2;
	if (line[1] == NULL)
	{
		printf("\n");
		return ;
	}
	while (line [i] && ft_strncmp(line[i], "-n", 2) == 0)
	{
		while (line[i][j] == 'n')
			j++;
		if (line[i][j] == '\0')
		{
			i++;
			nl = 1;
		}
		else
			break ;
		j = 2;
	}
	ft_echo_2(line, i, nl);
}