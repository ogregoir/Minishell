/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgreiner <rgreiner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 15:02:25 by ogregoir          #+#    #+#             */
/*   Updated: 2023/07/02 15:22:18 by rgreiner         ###   ########.fr       */
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

typedef	enum
{
	TOKEN_DOLLAR,
	TOKEN_PIPE,
	TOKEN_REDI_IN,
	TOKEN_REDI_EXIT,
	TOKEN_REDI_HERE_DOC,
	TOKEN_REDI_EXIT_APPEND,
	TOKEN_QUOTES,
	TOKEN_DB_QUOTES,
	TOKEN_TEXT,
	TOKEN_NULL
}e_token_type;

typedef struct s_lex
{
	char	*content;
	e_token_type		type;
	struct s_lex	*next;
	
}t_lex;

typedef struct{
	const char *token;
	int	len;
	e_token_type type;
}t_listtest;

static const t_listtest token[] =
{	
	{"<<", 2, TOKEN_REDI_HERE_DOC},
	{">>", 2, TOKEN_REDI_EXIT_APPEND},
	{"$", 1, TOKEN_DOLLAR},
	{"|", 1, TOKEN_PIPE},
	{"<", 1, TOKEN_REDI_IN},
	{">", 1, TOKEN_REDI_EXIT},
	{NULL, 1, 0}

};

	/*Lexer*/
void	ft_lexer(char **line, t_lex *lex);


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