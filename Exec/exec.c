/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgreiner <rgreiner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 12:46:31 by rgreiner          #+#    #+#             */
/*   Updated: 2023/11/07 23:57:30 by rgreiner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	ft_error(arg, ": command not found", "", 0);
	return (NULL);
}

char	*ft_find_path(char *arg, int i, t_global *data)
{
	char	**cmd;
	int		j;
	char	*path;
	char	*ret;

	j = -1;
	path = "PATH=";
	while (data->envmini[++j])
	{
		while (data->envmini[j][i] == path[i])
			i++;
		if (path[i] == '\0')
			break ;
		i = 0;
	}
	if (data->envmini[j] == NULL)
		ft_error("Didn't find a path", "", "", 1);
	cmd = ft_split(data->envmini[j], ':');
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
	while (tmp && (tmp->type == 8 || tmp->type == 0))
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

int	ft_check_cmd(t_lex *lex, t_global *data)
{
	char	*cmd;
	char	**arg;
	int		i;

	i = 0;
 	arg = malloc(sizeof(char *) * (ft_nbr_text(lex) + 1));
	while (lex && (lex->type == 8 || lex->type == 0))
	{
		arg[i] = ft_strdup(lex->content);
		i++;
		lex = lex->next;
	}
	arg[i] = NULL;
	if (access(arg[0], X_OK | F_OK) != 0)
	{
		cmd = ft_find_path(arg[0], 0, data);
		if (cmd == NULL)
			exit(127);
		execve(cmd, arg, data->envmini);
		exit(127);
	}
	execve(arg[0], arg, data->envmini);
	exit(127);
}

void	ft_not_builtin(t_lex *lex, t_global *data)
{
	if (lex->type != 8 && lex->type != 4)
		return ;
	data->error_code = detect_pipe(lex, data);
}
