/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 16:25:53 by rgreiner          #+#    #+#             */
/*   Updated: 2023/11/23 05:01:48 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	close_redi(int out, int file)
{
	if (file != 1)
	{
		dup2(out, STDOUT_FILENO);
		close(file);
		close(out);
	}
}

int	ft_multi_redi(t_lex *tmp)
{
	t_lex	*tmp2;

	tmp2 = tmp;
	tmp2 = tmp2->next;
	while (tmp2)
	{
		if (tmp2->type == 1)
			return (1);
		if (tmp2->type == 3 || tmp2->type == 5)
			return (0);
		tmp2 = tmp2->next;
	}
	return (1);
}

int	ft_builtin_redi2(t_lex *tmp, int file, int mod)
{
	file = openfile(tmp->next->content, mod);
	if (ft_multi_redi(tmp) == 1)
		return (file);
	close(file);
	return (1);
}

int	ft_builtin_redi(t_lex *lex, int file, int child)
{
	t_lex	*tmp;

	tmp = lex;
	while (tmp)
	{
		if (tmp->next && tmp->type == 3)
			file = ft_builtin_redi2(tmp, file, 1);
		if (tmp->next && tmp->type == 5)
			file = ft_builtin_redi2(tmp, file, 0);
		if (tmp->next && tmp->type == 2)
		{
			if (access(tmp->next->content, F_OK | R_OK) != 0)
				ft_error(tmp->next->content, ": No such file or directory" \
				, NULL, child);
		}
		if (tmp->type == 1)
			exit(1);
		tmp = tmp->next;
		if (file != 1)
			return (file);
	}
	return (1);
}

int	ft_verif2(t_global *data, t_lex *lex)
{
	char	*buf;
	char	*oldbuf;

	buf = NULL;
	buf = getcwd(buf, 100);
	oldbuf = ft_strdup(buf);
	if (ft_verif_cd(lex, data, oldbuf) == 1)
	{
		free (buf);
		free (oldbuf);
		return (1);
	}
	else if (ft_verif_cd(lex, data, oldbuf) == 2)
	{
		free(buf);
		free (oldbuf);
		return (0);
	}
	free (buf);
	free (oldbuf);
	return (2);
}
