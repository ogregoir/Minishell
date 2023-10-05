/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controles.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 17:53:23 by marvin            #+#    #+#             */
/*   Updated: 2023/09/04 17:53:23 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	non_canonique(void)
{
	struct termios	original;

	tcgetattr(STDIN_FILENO, &original);
	original.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &original);
}

void	ft_ctrlc(void)
{
	ft_putstr_fd("\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	ft_ctrld(void)
{
	rl_replace_line("", 0);
	rl_redisplay();
	printf("minishell: ");
}

void	ft_ctrlb(int sig)
{
	(void)sig;
	//printf("^C\n");
	rl_replace_line("", 0);
	rl_redisplay();
	//printf("minishell: ");
}

void	ft_controles(int sig)
{
	if (sig == SIGINT)
	{
		//printf("sig %d\n", sig);
		ft_ctrlc();
	}
	if (sig == SIGQUIT)
		ft_ctrld();
	else
		return ;
}
