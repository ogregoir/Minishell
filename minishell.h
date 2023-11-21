/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 02:20:01 by marvin            #+#    #+#             */
/*   Updated: 2023/11/21 04:39:10 by marvin           ###   ########.fr       */
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
# include <sys/types.h>
# include <sys/stat.h>
# include <dirent.h>

extern int	g_error;

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

typedef struct s_pipe
{
	int	in;
	int	pipenbr;
	int	out;
}t_pipe;

typedef struct s_quotes
{
	int		i;
	int		j;
	char	**str;
}t_quotes;

typedef struct s_lex
{
	struct s_lex	*next;
	char			*content;
	int				type;
}t_lex;

typedef struct s_dollar
{
	char	*dollar;
	char	*cpy;
	char	*env;
	char	*name;
	char	*end;
	char	*line;
	char	*linepos;
	char	*err_code;
	int		len;
}t_dollar;

typedef struct s_global
{
	char		**envmini;
	char		**env_exp;
	int			size_env;
	t_listtest	*token;
	int			**fd;
	int			*pid;
	int			file;
}t_global;

	/*BUILTINS*/

void	ft_exit(t_lex *lex);
int		ft_pwd(int file);
int		ft_env(t_lex *lex, t_global *data, int file);

int		ft_unset(t_lex *lex, t_global *data);
void	ft_moove_env(char *oldbuf, char *str, t_global *data);
int		ft_access_cd(t_global *data, char *buf, char *line, char *oldbuf);

int		ft_already_exists(t_global *data, char *str, int i);
int		ft_export(t_lex *lex, t_global *data);
int		ft_echo(t_lex *lex, int file);

int		ft_cd(t_global *data, t_lex *lex);

char	**ft_export2(t_lex *lex, t_global *data);

int		ft_verif_exp(t_lex *lex, t_global *data);
int		ft_export3(t_lex *lex, t_global *data);

	/*EXEC*/

int		ft_builtin(char *content, int type);
void	ft_exec_main(int file, t_lex *lex, t_global *data);
void	check_file(t_lex *lex);
t_lex	*ft_builtin_exec(t_global *data, t_lex *lex, int child, int i);

int		detect_pipe(t_lex *lex, t_global *data);

void	ft_pipex_in(int **fd, t_lex *lex, t_pipe *data);
void	check_dir(t_lex *lex);
void	endl(char *s, int fd);

int		ft_check_cmd(t_lex *lex, t_global *data);
int		ft_exec(t_lex *lex, t_global *data);

int		ft_create_tmp(char *line, int temp);
int		ft_strcmp(const char *s1, const char *s2);

int		check_here_doc(t_lex *lex, t_global *data);

int		check_redi(t_lex *lex);
int		openfile(char *content, int mod);

void	close_pipe(int **fd, int pipenbr);
int		**create_fd(int pipenbr, int **fd);
void	ft_pipe_create(int pipenbr, int **fd);

void	ft_pipex_main(int i, t_lex *lex, t_pipe *data, t_global *g);

void	ft_pipex_child(int i, t_lex *lex, t_pipe *data, t_global *global);

	/*LEXER*/

void	ft_init_token(t_global *data, char **env);
t_lex	*check_dollar(t_lex *lex, char *s);
t_lex	*ft_lexer(char **line, t_lex *lex, t_global *data);

char	*check_next(char *str, int j, int l, t_global *data);
int		copy_text(char *str);
t_lex	*ft_check_type(char *str, t_lex *lex, int j, t_global *data);

int		ft_nbr_space(char **str);
t_lex	*ft_join(t_lex *tofree, t_lex *tmp, t_lex *lex);

t_lex	*ft_lexer_quotes(char *line, t_lex *lex, int i, t_global *data);

	/*D-UTILS*/

void	close_redi(int out, int file);
int		ft_multi_redi(t_lex *tmp);
int		ft_builtin_redi(t_lex *lex, int file, int child);

char	*ft_convert_dollar(char *input, int size, t_global *data);

t_lex	*dollar_lexer(t_lex *lex, t_global *data);
char	*go_next(char *str, char *s);
int		check_err(t_lex *lex);

void	ft_free_list(t_lex *lex);
void	print_lexer(t_lex *lex);
void	ft_free_char(t_global *data);
void	ft_free_global(t_global *data);
void	ft_free_env_exp(t_global *data);

int		ft_detect_quotes(char *line, int i, int nbr_s, int nbr_d);
int		ft_check_nbr(char *str);
void	ft_free_split(char **split);
void	ft_error(char *arg, char *str, char *s, int pid);

int		ft_len_malloc(char *input, char *err_code, int size, t_global *data);
char	**create_env(char **env, t_global *data);
t_lex	*record_exp(t_lex *lex);

int		ft_last_ele(t_lex *lex, char *str);
int		ft_variable_exist(t_global *data, char *str);
char	*ft_strdup2(const char *src, int n);
char	*ft_strncpy(char *str, char *src, int i);
int		ft_strlen_char(t_global *data);

t_lex	*ft_lstnew(char *content, t_token_type i);
void	addcontent(t_lex *list, char *content, t_token_type i);
int		ft_isspace(int i);
char	*ft_get_env(char *str, char **env);
void	ft_free_data_envmini(t_global *data);

	/*CONTROLES*/

void	non_canonique(void);
void	ft_ctrlc(int sig);
void	ft_ctrlc2(int sig);
void	ft_ctrld(int sig);
void	ft_ctrlb(int sig);

	/*QUOTES*/

char	*ft_check_quote(char *line, int i);
t_lex	*ft_quote(char *line, t_lex *lex, int i, t_global *data);
char	*ft_dollar_err(t_dollar *d, char *input);

	/*UTILS*/

char	*ft_search_quote(char *line, char c, int i);
int		check_text(int text);
t_lex	*ft_text(char *str, int j, t_lex *lex, t_global *data);
void	freeold(char *env, char *name);
void	ft_check_dos(t_global **data, int i, char *buf);

#endif