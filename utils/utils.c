/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 14:17:35 by rgreiner          #+#    #+#             */
/*   Updated: 2023/11/08 02:00:08 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_detect_quotes(char *line)
{
	int	i;
	int	nbr_s;
	int	nbr_d;

	i = 0;
	nbr_s = 0;
	nbr_d = 0;
	while (line[i])
	{
		if (line[i] == 34)
		{
			i++;
			while (line[i] && line[i] != 34)
				i++;
			nbr_d++;
		}
		else if (line[i] == 39)
		{
			i++;
			while (line[i] && line[i] != 39)
				i++;
			nbr_s++;
		}
		else
			i++;
	}
	if (nbr_d == 0 && nbr_s == 0)
		return (0);
	nbr_s = nbr_s % 2;
	nbr_d = nbr_d % 2;
	if (nbr_d == 0 && nbr_s == 0)
		return (1);
	ft_error("Invalid numbers of quotes\n", NULL, NULL, 1);
	exit (1);
	return (0);
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

	i = 0;
	if(!split)
		return ;
	while (split[i] != NULL)
	{
		free(split[i]);
		split[i] = NULL;
		i++;
	}
	free(split);
	split = NULL;
}

void	ft_error(char *arg, char *str, char *s, int pid)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd(s, STDERR_FILENO);
	write(STDERR_FILENO, "\n", 1);
	if (pid == 0)
		exit(1);
}
