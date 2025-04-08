/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaile <mhaile@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 18:58:52 by akanbari          #+#    #+#             */
/*   Updated: 2024/02/04 14:43:05 by mhaile           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exec_commands2(t_minishell *minishell, t_cmd *tmp, int fpipe[2])
{
	if (ft_ifstrequal(tmp->cmd, EXIT_CMD) && tmp->type != T_PIPE
		&& (!tmp->prev || tmp->prev->type != T_PIPE))
	{
		exit_cmd(tmp->args_array, minishell, fpipe);
	}
	else if (ft_ifstrequal(tmp->cmd, EXPORT_CMD) && tmp->args)
	{
		if (minishell->count_cmds > 1)
			minishell->exit = 1;
		else
			export_cmd(minishell, tmp, 1);
	}
	else if (ft_ifstrequal(tmp->cmd, CD_CMD) && tmp->type != T_PIPE
		&& (!tmp->prev || tmp->prev->type != T_PIPE))
		cd_cmd(minishell, tmp);
	else if (ft_ifstrequal(tmp->cmd, UNSET_CMD))
		unset_cmd(minishell, tmp);
	else if (!tmp->prev || (tmp->prev && !(tmp->prev->type == T_PIPE)))
		exec_prog(minishell, tmp, fpipe, NULL);
}

void	go_commands(t_minishell *minishell, int fpipe[2], t_cmd *tmp)
{
	if ((tmp->out != -1 && tmp->in != -1) || (tmp->next))
	{
		if (pipe(fpipe))
			return ;
		minishell->fpip = fpipe;
		exec_commands2(minishell, tmp, fpipe);
		close(fpipe[0]);
		close(fpipe[1]);
	}
	if (!tmp->cmd && tmp->type != T_PIPE)
		process_args_env(minishell, tmp);
	while (tmp->type == T_PIPE)
		tmp = tmp->next;
}

//need checking for variables
void	exec_commands(t_minishell *minishell)
{
	t_cmd	*tmp;
	int		fpipe[2];
	int		process_flag;

	tmp = minishell->cmd_list;
	while (tmp)
	{
		process_flag = process_args(minishell, tmp);
		if (process_flag == -1)
			break ;
		create_redirect(minishell, tmp);
		if (g_exit_status == OFF_HERE_DOC)
		{
			while (tmp)
				tmp = tmp->next;
			g_exit_status = CTRL_C_ON_HEREDOC;
		}
		else
		{
			go_commands(minishell, fpipe, tmp);
			tmp = tmp->next;
		}
	}
}
