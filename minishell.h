/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgreiner <rgreiner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 02:20:01 by marvin            #+#    #+#             */
/*   Updated: 2023/09/30 17:04:07 by rgreiner         ###   ########.fr       */
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
# include <sys/wait.h> 
# include <termios.h>
# include <stddef.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "utils/libft/libft.h"

extern int error_code;

typedef enum s_test
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
}t_token_type;

typedef struct s_listtest{
	char			*token;
	int				len;
	t_token_type	type;
}t_listtest;

static const t_listtest	g_token[] = \
	{
{"<<", 2, TOKEN_REDI_HERE_DOC},
{">>", 2, TOKEN_REDI_EXIT_APPEND},
{"$", 1, TOKEN_DOLLAR},
{"|", 1, TOKEN_PIPE},
{"<", 1, TOKEN_REDI_IN},
{">", 1, TOKEN_REDI_EXIT},
{NULL, 1, TOKEN_NULL}
};

typedef struct s_pipe
{
	int	in;
	int pipenbr;
}t_pipe;

typedef struct s_lex
{
	struct s_lex	*next;
	char			*content;
	t_token_type	type;
}t_lex;



	/*Lexer*/
t_lex	*ft_lexer(char **line, t_lex *lex);
char	*check_next(char *str, int j, int l);
void	ft_variables_env(char *line);
t_lex	*ft_text(char *s, char *str, int j, t_lex *lex);
t_lex	*ft_check_type(char *str, t_lex *lex, int i, int j);
char	*go_next(char *str, char *s);
int		check_text(char text);


	/*Builtins*/
void	ft_exit(t_lex *lex);
int		ft_pwd(void);
int		ft_env(t_lex *lex, char **env);
int		ft_echo(t_lex *lex);
int		ft_cd(char **env, char **line);
int		ft_export(char **line, char **env);
int		ft_unset(char **line, char **env);

	/*Utils*/
void	ft_free_split(char **split);
int		ft_check_nbr(char *str);
t_lex	*ft_lstnew(char *content, t_token_type i);
void	addcontent(t_lex *list, char *content, t_token_type i);
int     ft_detect_quotes(char *line);
char	*ft_strdup2(const char *src, int n);
char	*ft_last_ele(t_lex *lex);



	/*EXEC*/
void	ft_not_builtin(t_lex *lex, char **env);
int		detect_pipe(t_lex *lex, char **envp);
int		ft_check_cmd(t_lex *lex, char **envp);

void	close_pipe(int **fd, int pipenbr);
int		**create_fd(int pipenbr, int **fd);
void	ft_pipe_create(int pipenbr, int **fd);
void	ft_pipex_child(int **fd, int i, t_lex *lex, t_pipe *data);
int		check_redi(t_lex *lex);
int		check_redi_in(t_lex *lex);


	/*quotes*/
t_lex	*ft_quote(char *line, t_lex *lex);
char	*ft_check_quote(char *line, int i);
char	*ft_search_quote(char *line, char c);
t_lex	*ft_lexer_quotes(char *line, t_lex *lex, int i);


	/*CONTROLES*/
void    non_canonique(void);
void    ft_controles(int sig);

void	ft_dollar(t_lex *lex);
char	*ft_oldpwd(char **env, char **line);
void	ft_free_oldpwd(char **env);
int		ft_oldbuf(char **env, char **line);
void	ft_oldpwd2(char **env, char *oldbuf);

int error_parentheses(char **line);
int no_such_directory(char **line);
int error_arguments(void);
int ft_dollar_env(t_lex *lex, char **env);

void	ft_error(char *arg);
void free_list(t_lex *lex);


#endif