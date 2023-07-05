/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgreiner <rgreiner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 12:46:31 by rgreiner          #+#    #+#             */
/*   Updated: 2023/07/05 17:22:48 by rgreiner         ###   ########.fr       */
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
	exit(EXIT_FAILURE);
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
	if (envp[j] == '\0')
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

void	ft_check_cmd(t_lex *lex, char **envp)
{
	char	*cmd;
	char	**arg;
	int		i;

	i = 0;
	arg = malloc(sizeof(char *) * (ft_nbr_text(lex) + 1));
	while (lex && lex->type == 8)
	{
		arg[i] = ft_strdup(lex->content);
		i++;
		lex = lex->next;
	}
	arg[i] = NULL;
	if (access(arg[0], X_OK | F_OK) != 0)
	{
		cmd = ft_find_path(arg[0], envp, 0);
		if (cmd == NULL)
			exit(EXIT_FAILURE);
		execve(cmd, arg, envp);
	}
	execve(arg[0], arg, envp);
	exit(EXIT_FAILURE);
}

void	ft_not_builtin(t_lex *lex, t_data *data, char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0 && lex->type == 8)
		ft_check_cmd(lex, envp);
	while (wait(0) > 0)
		;
	data->exit_status = 0;
}
