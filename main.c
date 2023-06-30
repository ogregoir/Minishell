/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgreiner <rgreiner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 15:02:15 by ogregoir          #+#    #+#             */
/*   Updated: 2023/06/30 14:54:37 by rgreiner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	check_line(char *rl_line_buffer)
{
	char **line;
	
	line = ft_split(rl_line_buffer, ' ');
	/*if(ft_strncmp(line, "echo", 4) == 0)
		ft_echo();
	else if(ft_strncmp(line, "cd", 2) == 0)
		ft_cd();*/
	if(ft_strncmp(line[0], "pwd", 3) == 0)
		ft_pwd();
	/*else if(ft_strncmp(line, "export", 6) == 0)
		ft_export();
	else if(ft_strncmp(line, "unset", 5) == 0)
		ft_unset();
	else if(ft_strncmp(line, "env", 3) == 0)
		ft_env();*/
	if(ft_strncmp(line[0], "exit", 4) == 0 && ft_strlen(line[0]) == 4)
		ft_exit(line);
	//else
	//	ft_not_builtin();
	ft_free_split(line);
		
}
int	main(int argc, char **argv, char **env)
{
	argc = 0;
	argv = NULL;
	env = NULL;

	readline("minishell : ");	
	while(rl_line_buffer != NULL)
	{
		check_line(rl_line_buffer);
		readline("minishell : ");
	}
	return (0);
}
