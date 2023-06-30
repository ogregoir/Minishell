/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgreiner <rgreiner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 14:17:58 by rgreiner          #+#    #+#             */
/*   Updated: 2023/06/30 15:31:00 by rgreiner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void	ft_exit(char **line)
{
	printf("exit\n");
	if (line[1] == NULL)
		exit (0);
	if (ft_check_nbr(line) == 1)
		{
			printf("minishell: exit: %s numeric argument required\n", line[1]);
			exit (1);
		}
	else
		exit (ft_atoi(line[1]));
}

void	ft_pwd(void)
{
	char *buf;
	int	i;

	i = 0;
	buf = NULL;
	while(buf == NULL)
	{
		buf = getcwd(buf, i);
		i++;
	}
	printf("%s\n", buf);
	free(buf);
}

void	ft_env(char **line, char **env)
{
	int i;

	i = 0;
	if (line[1] != NULL)
		{
		printf("env: %s: No such file or directory\n", line[1]);
		return ;
		}
	while(env[i] != NULL)
	{
		printf("%s\n", env[i]);
		i++;
	}
}