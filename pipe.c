/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 10:11:22 by rgreiner          #+#    #+#             */
/*   Updated: 2023/09/22 22:22:30 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int		check_redi(t_lex *lex)
{
	t_lex *tmp;

	tmp = lex;
	while(tmp)
	{
		if(tmp->type == 3 || tmp->type == 5)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	ft_pipex_main(int **fd, int pipenbr, int i, t_lex *lex)
{
	if(check_redi(lex) == 1)
	{
	while(lex && lex->type == 8)
		lex = lex->next;
	if(lex->type == 3)
		{
			lex = lex->next;
			dup2(open(lex->content, O_TRUNC | O_WRONLY | O_CREAT, 0644) ,STDOUT_FILENO);
		}
	if(lex->type == 5)
		{
			lex = lex->next;
			dup2(open(lex->content, O_APPEND | O_WRONLY | O_CREAT, 0644) ,STDOUT_FILENO);
		}
	if(lex->next)
		{
		if(lex->next->type == 3 || lex->next->type == 5)
			ft_pipex_main(fd, pipenbr, i, lex);
		}
	}
	dup2(fd[i][0], STDIN_FILENO);
	close_pipe(fd, pipenbr);
}

int	pipex(t_lex *lex, char **envp, int pipenbr)
{
	pid_t	*pid;
	int		**fd;
	int		i;
	int		ret;

	i = 0;
	fd = NULL;
	pid = malloc(sizeof(pid_t) * pipenbr + 1);
	fd = create_fd(pipenbr, fd);
	ft_pipe_create(pipenbr, fd);
	while (i <= pipenbr)
	{
		if(lex->type == 1)
			lex = lex->next;
		pid[i] = fork();
		if (i < pipenbr && pid[i] == 0)
			ft_pipex_child2(fd, pipenbr, i);
		else if (i == pipenbr && pid[i] == 0)
			ft_pipex_main(fd, pipenbr, i, lex);
		if (pid[i] == 0)
			ret = ft_check_cmd(lex, envp);
		i++;
		if(lex->next == NULL)
			break;
		while(lex && lex->type == 8)
			lex = lex->next;
	}
	close_pipe(fd, pipenbr);
	while (wait(0) > 0)
		;
	return(ret);
}

int detect_pipe(t_lex *lex, char **envp)
{
	int i;
	int	j;
    t_lex *tmp;
    
    tmp =  lex;
	i = 0;
	while(tmp->next)
	{
		if(tmp->type == 1)
			i++;
		if(tmp->type > 1)
			j++;
		tmp = tmp->next;
    }
	if(i > 0 || j > 0)
		{
			error_code = pipex(lex, envp, i);
			return (1);
		}
	return(0) ;
}
