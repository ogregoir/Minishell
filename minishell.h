/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgreiner <rgreiner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 15:02:25 by ogregoir          #+#    #+#             */
/*   Updated: 2023/07/01 18:43:06 by rgreiner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <stdarg.h>
# include <unistd.h>
# include <fcntl.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "utils/libft/libft.h"

typedef struct s_data
{
	int	exit_status;
}t_data;

typedef struct s_lex
{
	char	*content;
	int		type;
	struct s_lex	*next;
}t_lex;


void ft_variables_env(char *line);
	/*Builtins*/
void	ft_exit(char **line, t_data *data);
void	ft_pwd(t_data *data);
void	ft_env(char **line, char **env, t_data *data);
void	ft_echo(char **line, int nl, t_data *data);

	/*Utils*/
void	ft_free_split(char **split);
int		ft_check_nbr(char **str);

#endif