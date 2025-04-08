/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaile <mhaile@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:48:23 by mhaile            #+#    #+#             */
/*   Updated: 2024/02/04 13:14:36 by mhaile           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	handle_errno(t_minishell *minishell, char *cmd, int type)
{
	if (type == 14)
		ft_printf_fd(2, "minishell: %s: %s\n", cmd,
			"command not found");
	else
		ft_printf_fd(2, "minishell: %s: %s\n", cmd, strerror(errno));
	minishell->exit = 127;
	minishell->exit = 127;
	if (type == 13)
		minishell->exit = 126;
}

int	ft_strlen_s(char *s)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != ' ')
			count++;
		i++;
	}
	return (count);
}

void	initialize_minishell(t_minishell *minishell, char **envp)
{
	minishell->line_buf = NULL;
	minishell->token_list = NULL;
	minishell->env_sorted_list = NULL;
	minishell->exit = 0;
	minishell->exit_str = NULL;
	minishell->env_array = envp;
	minishell->env_array_local = NULL;
	minishell->env_list = NULL;
	minishell->cmd_list = NULL;
	minishell->quit2 = 0;
	minishell->quit = 0;
	minishell->forked = 0;
	minishell->exit_str = NULL;
	minishell->bin = NULL;
	minishell->curdir = NULL;
	minishell->name = NULL;
	init_env_list(minishell, envp);
}

void	start_exec(t_minishell *shell, int *exit_status)
{
	add_history(shell->line_buf);
	start_parse(shell, shell->line_buf);
	shell->count_cmds = cmd_list_size(&shell->cmd_list);
	if (shell->cmd_list)
		exec_commands(shell);
	if (ft_strlen(shell->line_buf) && ft_strlen_s(shell->line_buf) == 0)
		shell->exit = 0;
	shell->exit = *exit_status;
}

int	read_and_execute(const char *prompt, t_minishell *shell)
{
	shell->line_buf = readline(prompt);
	if (!shell->line_buf || ft_strcmp(shell->line_buf, "exit") == 0)
	{
		shell->exit = 0;
		ft_printf_fd(STDOUT_FILENO, "exit\n");
		free_and_exit(shell, shell->exit);
	}
	if (!init_valid_line(&shell->line_buf, shell))
	{
		ft_strdel(&shell->line_buf);
		return (0);
	}
	start_exec(shell, &shell->exit);
	return (1);
}
