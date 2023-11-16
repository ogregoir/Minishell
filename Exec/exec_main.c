/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgreiner <rgreiner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 12:59:38 by rgreiner          #+#    #+#             */
/*   Updated: 2023/11/16 16:08:51 by rgreiner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

pid_t	*init_data(t_global *datas, t_pipe *data, pid_t *pid)
{
	datas->fd = NULL;
	data->in = 0;
	data->out = 0;
	datas->file = 0;
	datas->fd = create_fd(data->pipenbr, datas->fd);
	pid = malloc(sizeof(pid_t) * (data->pipenbr + 1));
	return (pid);
}

void	exec_loop(t_lex *lex, t_global *datas, t_pipe data, int i)
{
	pid_t	*pid;

	pid = 0;
	pid = init_data(datas, &data, pid);
	ft_pipe_create(data.pipenbr, datas->fd);
	while (lex && ++i <= data.pipenbr)
	{
		if (lex->type == 1)
			lex = lex->next;
		datas->file = check_here_doc(lex, datas);
		if (datas->file == -1)
			break ;
		pid[i] = fork();
		if (i < data.pipenbr && pid[i] == 0)
			ft_pipex_child(i, lex, &data, datas);
		else if (i == data.pipenbr && pid[i] == 0)
			ft_pipex_main(i, lex, &data, datas);
		if (lex->next && lex->next->next && lex->type == 4)
			lex = lex->next->next;
		if (pid[i] == 0 && ft_builtin(lex->content, 1) != 0)
			datas->error_code = ft_check_cmd(lex, datas);
		while (lex && lex->type != 1)
			lex = lex->next;
	}
	free(pid);
}

void	pipex(t_lex *lex, t_global *datas, int nbrpipe, int i)
{
	t_pipe	data;

	data.pipenbr = nbrpipe;
	exec_loop(lex, datas, data, i);
	close_pipe(datas->fd, data.pipenbr);
	unlink("temp");
}

int	detect_pipe(t_lex *lex, t_global *data)
{
	int		i;
	int		status;
	int		j;
	t_lex	*tmp;

	tmp = lex;
	status = 0;
	i = 0;
	j = 0;
	while (tmp)
	{
		if (tmp->type == 1)
			i++;
		if (tmp->type > 1 && tmp->type != 8 && tmp->type != 0)
			j++;
		tmp = tmp->next;
	}
	pipex(lex, data, i, -1);
	while (wait(&status) > 0)
		;
	return (WEXITSTATUS(status));
}
