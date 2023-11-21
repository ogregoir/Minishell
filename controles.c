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

void	ft_ctrlc(int sig)
{
	(void)sig;
	ft_putstr_fd("\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_error = 130;
}

void	ft_ctrlc2(int sig)
{
	(void)sig;
	ft_putstr_fd("\n", 1);
	rl_replace_line("", 0);
	rl_redisplay();
	g_error = 130;
}

void	ft_ctrld(int sig)
{
	(void)sig;
	printf("minishell: ");
	rl_replace_line("", 0);
	rl_redisplay();
	g_error = 127;
}

void	ft_ctrlb(int sig)
{
	(void)sig;
	rl_replace_line("", 0);
	rl_redisplay();
	g_error = 131;
}
