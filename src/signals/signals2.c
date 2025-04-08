/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaile <mhaile@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 15:46:06 by mhaile            #+#    #+#             */
/*   Updated: 2024/02/04 13:14:55 by mhaile           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	signal_handler_commands(int num)
{
	if (num == SIGINT)
		write(1, "\n", 1);
	else if (num == SIGQUIT)
		ft_putstr_fd("Quit: 3\n", 2);
}

void	signal_handler(int signum)
{
	if (signum == SIGQUIT)
		;
	else if (signum == SIGINT)
	{
		ft_printf_fd(STDERR_FILENO, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_exit_status = 0;
	}
}

void	setup_signals_bash(t_minishell *minishell)
{
	(void)minishell;
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}
