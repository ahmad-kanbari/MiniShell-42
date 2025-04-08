/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaile <mhaile@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 18:43:27 by mhaile            #+#    #+#             */
/*   Updated: 2024/02/04 16:05:06 by mhaile           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	execve_prog(t_minishell *minishell, t_cmd *tmp, int *fpip, int *spip)
{
	exeve_checker(minishell, tmp, fpip, spip);
	if (minishell->env_array_local)
		ft_free_split(&minishell->env_array_local);
	minishell->env_array_local = env_to_array(minishell);
	execve(tmp->bin, tmp->args_array, minishell->env_array_local);
	minishell->exit = errno;
	handle_errno(minishell, tmp->cmd, errno);
	close_fds(fpip, spip);
	free_child(minishell, minishell->exit);
}

void	exec_child(t_minishell *minishell, t_cmd *cmd, int fpip[2], int spip[2])
{
	if (cmd->out == -1 || cmd->in == -1)
		free_child(minishell, 1);
	handle_fd(cmd, fpip, spip);
	exec(minishell, cmd, fpip, spip);
}

void	exec_prog(t_minishell *minishell, t_cmd *cmd, int fpip[2], int spip[2])
{
	pid_t	pid;

	minishell->forked = 1;
	ft_free_split(&cmd->args_array);
	cmd->args_array = join_args(minishell, cmd);
	set_signals_exec();
	pid = fork();
	if (pid < 0)
		free_and_exit(minishell, errno);
	if (pid == 0)
		exec_child(minishell, cmd, fpip, spip);
	else
	{
		if (access("child_pid.tmp", F_OK) == 0)
			wait(NULL);
		if (find_heredoc(minishell))
			wait(NULL);
		if (cmd->type == T_PIPE && cmd->prev && cmd->prev->type == T_PIPE
			&& !close(fpip[1]) && !close(fpip[0]))
			exec_prog2(minishell, cmd, pid, spip);
		else
			exec_prog2(minishell, cmd, pid, fpip);
	}
}

void	exec2(t_minishell *minishell, t_cmd *tmp, int *fpip, int *spip)
{
	if (ft_ifstrequal(tmp->cmd, EXPORT_CMD))
	{
		if (minishell->count_cmds >= 1)
		{
			export_cmd(minishell, tmp, 1);
			g_exit_status = 1;
		}
	}
	else if (ft_ifstrequal(tmp->cmd, UNSET_CMD))
		free_child(minishell, 0);
	else if (tmp->cmd && minishell->env_array != NULL
		&& tmp->args_array != NULL )
		execve_prog(minishell, tmp, fpip, spip);
}

void	exec(t_minishell *minishell, t_cmd *tmp, int *fpip, int *spip)
{
	if (ft_ifstrequal(tmp->cmd, ECHO_CMD))
		echo_cmd(minishell, tmp);
	else if (ft_ifstrequal(tmp->cmd, CD_CMD))
		cd_cmd(minishell, tmp);
	else if (ft_ifstrequal(tmp->cmd, EXIT_CMD))
	{
		if (spip != NULL)
		{
			if (spip[0])
				close(spip[0]);
			if (spip[1])
				close(spip[1]);
		}
		exit_cmd(tmp->args_array, minishell, fpip);
		free_child(minishell, minishell->exit);
	}
	else if (ft_ifstrequal(tmp->cmd, ENV_CMD))
		env_cmd(minishell, &minishell->env_list);
	else if (ft_ifstrequal(tmp->cmd, PWD_CMD))
		pwd_cmd(minishell);
	else
		exec2(minishell, tmp, fpip, spip);
	close_fds(fpip, spip);
	free_child(minishell, minishell->exit);
}
