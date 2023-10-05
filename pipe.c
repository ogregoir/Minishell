/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 10:11:22 by rgreiner          #+#    #+#             */
/*   Updated: 2023/10/04 21:08:09 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"


int		check_redi_out(t_lex *lex)
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

int		check_redi(t_lex *lex)
{
	t_lex *tmp;

	tmp = lex;
	while(tmp)
	{
		if(tmp->type == 3 || tmp->type == 5 || tmp->type == 2)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int		openfile(char *content, int mod)
{
	int file;

	if(mod == 0)
		file = open(content, O_APPEND | O_WRONLY | O_CREAT, 0644);
	if(mod == 1)
		file = open(content, O_TRUNC | O_WRONLY | O_CREAT, 0644);
	if(file < 0 )
		{
			ft_putendl_fd(" Permission denied", 2);
			exit(1);
		}
	return(file);
}

void	ft_pipex_main(int **fd, int i, t_lex *lex, t_pipe *data)
{
	int file;
	
	if(check_redi(lex) == 1)
	{
	while(lex && lex->type == 8)
		lex = lex->next;
	if(lex->type == 2)
		{
			lex = lex->next;
			if(lex == NULL)
			{
				ft_putendl_fd("minishell: syntax error near unexpected token `newline'", 2);
				exit (1);
			}
			if(open(lex->content, O_RDONLY) == -1)
			{
				ft_error(lex->content, ": No such file or directory", 1);
				close_pipe(fd, data->pipenbr);
				exit(1);
			}
			dup2(open(lex->content, O_RDONLY), STDIN_FILENO);
			data->in = 1;
			if(lex->next)
					lex = lex->next;
		}
	if(lex->type == 3)
		{
			lex = lex->next;
			if(lex == NULL)
			{
				ft_putendl_fd("minishell: syntax error near unexpected token `newline'", 2);
				exit (1);
			}
			file = openfile(lex->content, 1);
			dup2(file, STDOUT_FILENO);
			if(data-> in == 0)
				dup2(fd[i][0], STDIN_FILENO);
		}
	if(lex->type == 5)
		{
			lex = lex->next;
			if(lex == NULL)
			{
				ft_putendl_fd("minishell: syntax error near unexpected token `newline'", 2);
				exit (1);
			}
			file = openfile(lex->content, 0);
			dup2(file ,STDOUT_FILENO);
			if(data-> in == 0)
				dup2(fd[i][0], STDIN_FILENO);
		}
	if(lex->next)
		{
		if(lex->next->type == 3 || lex->next->type == 5 || lex->next->type == 2 || lex->type == 2)
			ft_pipex_main(fd, i, lex, data);
		}
	}
	else
		dup2(fd[i][0], STDIN_FILENO);
	close_pipe(fd, data->pipenbr);
}

int	pipex(t_lex *lex, t_global *datas, int nbrpipe)
{
	pid_t	*pid;
	t_pipe	data;
	int		**fd;
	int		i;
	int		status;
	
	i = 0;
	status = 0;
	fd = NULL;
	data.pipenbr = nbrpipe;
	data.in = 0;
	pid = malloc(sizeof(pid_t) * data.pipenbr + 1);
	fd = create_fd(data.pipenbr + 1, fd);
	ft_pipe_create(data.pipenbr, fd);
	while (i <= data.pipenbr)
	{
		if(lex->type == 1)
			lex = lex->next;
		pid[i] = fork();
		if (i < data.pipenbr && pid[i] == 0)
			ft_pipex_child(fd, i, lex, &data);
		else if (i == data.pipenbr && pid[i] == 0)
			ft_pipex_main(fd, i, lex, &data);
		if (pid[i] == 0)
			datas->error_code = ft_check_cmd(lex, datas);
		i++;
		if(lex->next == NULL)
			break;
		while(lex && lex->type != 1)
			lex = lex->next;
	}
	close_pipe(fd, data.pipenbr);
	while (wait(&status) > 0)
		;
	if(WEXITSTATUS(status) == 1)
		datas->error_code = 1;
	else
		datas->error_code = 0;
	return(datas->error_code);
}

int detect_pipe(t_lex *lex, t_global *data)
{
	int i;
	int	j;
    t_lex *tmp;
    
    tmp =  lex;
	i = 0;
	j = 0;
	while(tmp)
	{
		if(tmp->type == 1)
			i++;
		if(tmp->type > 1 && tmp->type != 8)
			j++;
		tmp = tmp->next;
    }
	if(i > 0 || j > 0)
		{
			data->error_code = pipex(lex, data, i);
			return (1);
		}
	return(0) ;
}
