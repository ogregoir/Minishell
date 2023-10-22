/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgreiner <rgreiner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 09:37:09 by rgreiner          #+#    #+#             */
/*   Updated: 2023/10/20 14:55:47 by rgreiner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned int	s;

	s = 0;
	while (s1[s] != '\0' && s2[s] != '\0' && s1[s] == s2[s])
		s++;
	return (*(unsigned char *)(s1 + s) - *(unsigned char *)(s2 + s));
}

int	ft_create_tmp(char *line, int temp)
{
	int	i;

	i = 0;
	line = ft_strjoin(line, "\n");
	while (line[i])
	{
		write(temp, &line[i], 1);
		i++;
	}
	return (temp);
}


int ft_here_doc_open(t_lex *lex, int child)
{
	int		temp;
    int     file;
	char	*line;
	char	*cmp;
    if(!lex->next)
        {
            ft_error("", " syntax error near unexpected token `newline", child);
            return(-1) ;
        }
    lex = lex->next;
	cmp = lex->content;
	if(access("temp", F_OK | W_OK) == 0)
		unlink("temp");
	temp = open("temp", O_CREAT | O_RDWR | O_APPEND, 0644);
	line = readline("> ");
	while (1)
	{
		if (line != NULL)
		{
			if (ft_strcmp(line, cmp) == 0)
				break ;
			if(ft_strlen(line) > 1 && getenv(line + 1) != NULL)
				temp = ft_create_tmp(getenv(line + 1), temp);
			else
				temp = ft_create_tmp(line, temp);
			free(line);
		}
		line = readline("> ");
	}
	free(line);
	file = open("temp", O_RDONLY);
    return(file);
}

int ft_here_doc(t_lex *lex, int child, int **fd, t_pipe *data)
{
	int pid;
	int fd2[2];
	int file;
	
	pipe(fd2);
	file = 0;
	pid = fork();
	if(pid == 0)
		{
			close(fd2[0]);
			file = ft_here_doc_open(lex, child);
			write(fd2[1], &file, sizeof(file));
			close(fd2[1]);
			close_pipe(fd, data->pipenbr);
			exit(0);
		}
	close(fd2[1]);
	waitpid(pid, NULL, 0);
	read(fd2[0], &file, sizeof(file));
	close(fd2[0]);
	return (file);
}