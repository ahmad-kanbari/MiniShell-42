/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akanbari <akanbari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 20:22:36 by akanbari          #+#    #+#             */
/*   Updated: 2024/02/02 17:30:02 by akanbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	add_cmd_list(t_minishell *shell, t_cmd **begin, t_cmd *new)
{
	t_cmd	*tmp;

	if (!new || !begin)
		return ;
	new->cmd = supp_newline(shell, new->cmd);
	if (*begin)
	{
		tmp = *begin;
		while (tmp->next)
		{
			tmp->next->prev = tmp;
			tmp = tmp->next;
		}
		tmp->next = new;
		new->prev = tmp;
		new->next = NULL;
	}
	else
		*begin = new;
}

void	clear_cmd_node_free(t_cmd *cmd)
{
	if (cmd->cmd)
		ft_strdel(&(cmd->cmd));
	if (cmd->bin)
		ft_strdel(&cmd->bin);
	if (cmd->args_array)
		ft_free_split(&(cmd->args_array));
	if (cmd->args)
		clear_token_list(&cmd->args);
	if (cmd->in)
		close(cmd->in);
	if (cmd->out)
		close(cmd->out);
}

void	clear_cmd_list(t_cmd **begin, void (*del)(void *))
{
	t_cmd		*tmp;
	t_cmd		*tmp2;
	t_token		*args;
	t_token		*args2;

	if (!begin || !del)
		return ;
	tmp = *begin;
	while (tmp)
	{
		clear_cmd_node_free(tmp);
		args = tmp->args;
		while (args)
		{
			ft_strdel(&args->word);
			args2 = args->next;
			free(args);
			args = args2;
		}
		tmp2 = tmp->next;
		free(tmp);
		tmp = tmp2;
	}
	*begin = NULL;
}

void	clear_cmd_node_free_child(t_cmd *cmd)
{
	if (cmd->cmd)
		ft_strdel(&(cmd->cmd));
	if (cmd->args)
		clear_token_list(&cmd->args);
	if (cmd->in)
		close(cmd->in);
	if (cmd->out)
		close(cmd->out);
}

void	clear_cmd_list_child(t_cmd **begin, void (*del)(void *))
{
	t_cmd		*tmp;
	t_cmd		*tmp2;
	t_token		*args;
	t_token		*args2;

	if (!begin || !del)
		return ;
	tmp = *begin;
	while (tmp)
	{
		clear_cmd_node_free_child(tmp);
		args = tmp->args;
		while (args)
		{
			ft_strdel(&args->word);
			args2 = args->next;
			free(args);
			args = args2;
		}
		tmp2 = tmp->next;
		free(tmp);
		tmp = tmp2;
	}
	*begin = NULL;
}
