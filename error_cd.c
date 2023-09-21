/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 16:24:57 by marvin            #+#    #+#             */
/*   Updated: 2023/09/21 16:24:57 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error_parentheses(char **line)
{
	printf("-minishell: syntax error near unexpected token `%c'\n", 
		line[1][0]);
	return (2);
}

int	no_such_directory(char **line)
{
	printf ("-minishell: cd: %s: No such file or directory\n", line[1]);
	return (1);
}

int	error_arguments(void)
{
	printf("-minishell: cd: too many arguments\n");
	return (1);
}
