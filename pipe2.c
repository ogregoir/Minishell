/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgreiner <rgreiner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 15:18:39 by rgreiner          #+#    #+#             */
/*   Updated: 2023/09/17 15:20:00 by rgreiner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void	close_pipe(int **fd, int pipenbr)
{
	int	j;

	j = 0;
	while (j <= pipenbr)
	{
		close(fd[j][0]);
		close(fd[j][1]);
		j++;
	}
}

int	**create_fd(int pipenbr, int **fd)
{
	int	i;

	i = 0;
	fd = malloc(sizeof(fd) * pipenbr);
	while (i <= pipenbr)
	{
		fd[i] = malloc(sizeof(*fd) * 2);
		i++;
	}
	return (fd);
}

void	ft_pipe_create(int pipenbr, int **fd)
{
	int	j;

	j = 0;
	while (j <= pipenbr)
	{
		pipe(fd[j]);
		j++;
	}
}

void	ft_pipex_child(int **fd, int pipenbr, int i)
{
	dup2(fd[i][0], STDIN_FILENO);
	dup2(fd[i + 1][1], STDOUT_FILENO);
	close_pipe(fd, pipenbr);
}

void	ft_pipex_child2(int **fd, int pipenbr, int i)
{
	if (i == 0)
	{
		ft_pipex_child(fd, pipenbr, i);
		return ;
	}
	dup2(fd[i][0], STDIN_FILENO);
	dup2(fd[i + 1][1], STDOUT_FILENO);
	close_pipe(fd, pipenbr);
}