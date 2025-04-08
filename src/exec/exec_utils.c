/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaile <mhaile@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 15:09:49 by akanbari          #+#    #+#             */
/*   Updated: 2024/02/04 13:12:52 by mhaile           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	close_fds(int fpip[2], int spip[2])
{
	if (fpip != NULL)
	{
		if (fpip[0])
			close(fpip[0]);
		if (fpip[1])
			close(fpip[1]);
	}
	if (spip != NULL)
	{
		if (spip[0])
			close(spip[1]);
		if (spip[1])
			close(spip[0]);
	}
}

//we are always read form zero and write in 1;
void	handle_fd(t_cmd *tmp, int fpip[2], int spip[2])
{
	if (tmp->prev && tmp->prev->type == T_PIPE)
	{
		dup2(fpip[0], 0);
		close(fpip[1]);
		if (tmp->type == T_PIPE)
		{
			dup2(spip[1], 1);
			close(spip[0]);
		}
	}
	else if (tmp->type == T_PIPE)
	{
		dup2(fpip[1], 1);
		close(fpip[0]);
	}
	if (tmp->out)
	{
		dup2(tmp->out, STDOUT_FILENO);
		close(tmp->out);
	}
	if (tmp->in)
	{
		dup2(tmp->in, STDIN_FILENO);
		close(tmp->in);
	}
}

int	find_heredoc(t_minishell *minishell)
{
	t_token	*tmp;

	tmp = minishell->token_list;
	while (tmp)
	{
		if (ft_ifstrequal(tmp->word, "<<"))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	proc_redir(t_minishell *minishell, t_cmd *tmp, int fpip[2], int spip[2])
{
	process_args(minishell, tmp->next);
	create_redirect(minishell, tmp->next);
	if (g_exit_status == OFF_HERE_DOC)
	{
		while (tmp->next)
			tmp = tmp->next;
		g_exit_status = CTRL_C_ON_HEREDOC;
	}
	while (tmp->next && !tmp->next->cmd)
	{
		process_args(minishell, tmp->next);
		create_redirect(minishell, tmp->next);
		tmp = tmp->next;
	}
	if (tmp->next)
	{
		process_args(minishell, tmp->next);
		create_redirect(minishell, tmp->next);
		exec_prog(minishell, tmp->next, fpip, spip);
	}
}

void	exec_prog2(t_minishell *minishell, t_cmd *tmp, pid_t pid, int fpip[2])
{
	int		status;
	int		spip[2];

	status = 0;
	if (pipe(spip) < 0)
		return ;
	minishell->fpip = fpip;
	minishell->spip = spip;
	if (tmp->type == T_PIPE)
		proc_redir(minishell, tmp, fpip, spip);
	close_fds(fpip, spip);
	waitpid(pid, &status, WUNTRACED);
	if (WIFEXITED(status) && tmp->type != T_PIPE)
		minishell->exit = WEXITSTATUS(status);
	else if (WIFSIGNALED(status) && tmp->type != T_PIPE)
		minishell->exit = WTERMSIG(status) + 128;
}
