/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgreiner <rgreiner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 14:17:58 by rgreiner          #+#    #+#             */
/*   Updated: 2023/06/30 18:14:39 by rgreiner         ###   ########.fr       */
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

void	ft_echo(char **line)
{
	int	i;
	int	nl;

	i = 1;
	nl = 0;
	if (line[1] == NULL)
	{
		printf("\n");
		return ;
	}
	while (line [i] && ft_strncmp(line[i], "-n", 2) == 0 && ft_strlen(line[i]) == 2)
	{
		i++;
		nl = 1;
	}
	while (line[i])
	{
		printf("%s", line[i]);
		printf(" ");
		i++;
	}
	if (nl == 0)
		printf("\n");
}
