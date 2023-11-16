/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgreiner <rgreiner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 14:31:17 by rgreiner          #+#    #+#             */
/*   Updated: 2023/11/16 14:38:43 by rgreiner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_pipex_in(int **fd, t_lex *lex, t_pipe *data)
{
	lex = lex->next;
	if (open(lex->content, O_RDONLY) == -1)
	{
		ft_error(lex->content, ": No such file or directory", NULL, 1);
		close_pipe(fd, data->pipenbr);
		exit(1);
	}
	dup2(open(lex->content, O_RDONLY), STDIN_FILENO);
}

void	check_dir(t_lex *lex)
{
	DIR	*dir;

	dir = NULL;
	if (lex->type != 8)
		return ;
	dir = opendir(lex->content);
	if (ft_strchri(lex->content, 47) != -1)
	{
		if (access(lex->content, X_OK) != 0)
		{
			ft_error("", lex->content, ": No such file or directory", 1);
			exit(127);
		}
	}
	if (dir)
	{
		ft_error("", lex->content, ": Is a directory", 1);
		closedir(dir);
		exit(126);
	}
	else
		return ;
}

void	endl(char *s, int fd)
{
	int		i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
	write(fd, "\n", 1);
}
