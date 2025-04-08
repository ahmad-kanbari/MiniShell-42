/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaile <mhaile@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 01:13:37 by akanbari          #+#    #+#             */
/*   Updated: 2024/02/04 15:45:30 by mhaile           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_minishell		minishell;

	(void)argv;
	if (argc != 1)
	{
		ft_putstr_fd("Error: too many arguments\n", 2);
		return (127);
	}
	ft_bzero(&minishell, sizeof(t_minishell));
	initialize_minishell(&minishell, envp);
	minishell.curdir = getcwd(NULL, 0);
	while (1)
	{
		g_exit_status = 0;
		setup_signals_bash(&minishell);
		minishell.fpip = NULL;
		minishell.spip = NULL;
		read_and_execute("\033[0;35mMiniShell:)\033[0m$ ", &minishell);
		free_clean(&minishell);
	}
	free_and_exit(&minishell, minishell.exit);
	return (minishell.exit);
}
