/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 12:46:31 by rgreiner          #+#    #+#             */
/*   Updated: 2023/09/15 03:49:49 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_find_cmd(char **cmd, char *arg)
{
	int		i;
	char	*tmp;
	char	*tmp2;

	i = 0;
	while (cmd[i])
	{
		tmp = ft_strjoin(cmd[i], "/");
		tmp2 = ft_strjoin(tmp, arg);
		free(tmp);
		if (access(tmp2, F_OK | X_OK) == 0)
			return (tmp2);
		i++;
		free(tmp2);
	}
	printf("minishell: %s: command not found\n", arg);
	return (NULL);
}

char	*ft_find_path(char *arg, char **envp, int i)
{
	char	**cmd;
	int		j;
	char	*path;
	char	*ret;

	j = -1;
	path = "PATH=";
	while (envp[++j])
	{
		while (envp[j][i] == path[i])
			i++;
		if (path[i] == '\0')
			break ;
		i = 0;
	}
	if (envp[j] == NULL)
	{
		perror("Didn't find a path");
		exit (EXIT_FAILURE);
	}
	cmd = ft_split(envp[j], ':');
	cmd[0] = ft_strtrim(cmd[0], "PATH=");
	ret = ft_find_cmd(cmd, arg);
	ft_free_split(cmd);
	return (ret);
}

int	ft_nbr_text(t_lex *lex)
{
	int		i;
	t_lex	*tmp;

	i = 0;
	tmp = lex;
	while (tmp && tmp->type == 8)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

int	ft_check_cmd(t_lex *lex, char **envp)
{
	char	*cmd;
	char	**arg;
	int		i;

	i = 0;
	arg = malloc(sizeof(char *) * (ft_nbr_text(lex) + 1));
	while (lex && lex->type == 8)
	{
		arg[i] = ft_strdup(lex->content);
		if(i > 1)
			arg[i] = ft_strjoin_free(arg[i - 1], arg[i]);
		i++;
		lex = lex->next;
	}	
	arg[i] = NULL;
	if (access(arg[0], X_OK | F_OK) != 0)
	{
		cmd = ft_find_path(arg[0], envp, 0);
		if (cmd == NULL)
				return(127);
		execve(cmd, arg, envp);
		return(126);
	}
	execve(arg[0], arg, envp);
	return(126);
}

void ft_not_builtin(t_lex *lex, char **envp)
{
	pid_t	pid;
	int		ret;
	int		fd[2];

	ret = 0;
	if(lex->type != 8)
		return ;
	if(detect_pipe(lex, envp) == 1)
		return ;
	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		ret = ft_check_cmd(lex, envp);
		write(fd[1], &ret, sizeof(ret));
		close(fd[1]);
		exit(EXIT_FAILURE);
	}
	close(fd[1]);
	while (wait(0) > 0)
		;
	read(fd[0], &ret, sizeof(ret));
	close(fd[0]);
	error_code = ret;
}
