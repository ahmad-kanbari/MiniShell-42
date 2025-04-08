/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaile <mhaile@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 19:15:56 by akanbari          #+#    #+#             */
/*   Updated: 2024/02/04 13:15:58 by mhaile           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	handle_non_numeric_arg(char *arg, t_minishell *shell)
{
	(void)shell;
	ft_printf("exit\n");
	ft_printf_fd(STDERR_FILENO,
		"minishell: exit: %s: numeric argument required\n", arg);
	shell->exit = 255;
}

static void	handle_too_many_args(t_minishell *shell)
{
	(void)shell;
	ft_printf("exit\n");
	ft_printf_fd(STDERR_FILENO, "minishell: exit: too many arguments\n");
	shell->exit = 1;
}

static void	exit_cmd_helper(char **argv, t_minishell *shell, int fpipe[2])
{
	long long	exit_code;

	ft_printf_fd(2, "exit\n");
	close(fpipe[0]);
	close(fpipe[1]);
	exit_code = ft_atol(argv[1]);
	if (((exit_code == -1) && (ft_strcmp(argv[1], "-1"))) \
		|| ((exit_code == 0) && (ft_strcmp(argv[1], "0"))))
	{
		ft_printf_fd(STDERR_FILENO, "minishell: exit: %s: \
			numeric argument required\n", argv[1]);
		free_and_exit(shell, 255);
	}
	free_and_exit(shell, exit_code);
}

void	exit_cmd(char **argv, t_minishell *shell, int fpipe[2])
{
	if (argv[1])
	{
		if (!ft_isnumeric(argv[1]))
		{
			close(fpipe[0]);
			close(fpipe[1]);
			handle_non_numeric_arg(argv[1], shell);
			free_and_exit(shell, shell->exit);
		}
		else if (argv[2])
			handle_too_many_args(shell);
		else
			exit_cmd_helper(argv, shell, fpipe);
	}
}
