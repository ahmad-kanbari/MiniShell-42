/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaile <mhaile@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 14:34:47 by mhaile            #+#    #+#             */
/*   Updated: 2024/02/04 14:49:40 by mhaile           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	add_more_args(t_minishell *minishell, t_cmd *cmd, char **split)
{
	int		i;
	char	*tmp;

	i = ft_count_split(split) - 1;
	tmp = cmd->cmd;
	cmd->cmd = ft_strdup(split[0]);
	free(tmp);
	while (i > 0)
	{
		add_token_front(&cmd->args, \
			create_arg_token(minishell, split[i], T_WORD));
		i--;
	}
}

//need to be checked
void	process_args_env(t_minishell *minishell, t_cmd *cmd)
{
	t_env	*tmp;

	(void)* cmd;
	tmp = minishell->env_list;
	while (tmp)
	{
		tmp->key = handle_quotes(minishell, tmp->key, 1);
		tmp = tmp->next;
	}
}

//adding more tokens to the list and removing the $sign
t_token	*add_more_args2(t_minishell *shell, t_cmd *cmd,
					t_token **token, char **split)
{
	t_token	*new;
	t_token	*end_new;
	t_token	*next;

	new = token_split_to_list(shell, split);
	end_new = new;
	while (end_new->next)
		end_new = end_new->next;
	next = (*token)->next;
	end_new->next = next;
	if ((*token)->next)
		(*token)->next->prev = end_new;
	if ((*token)->prev)
		(*token)->prev->next = new;
	else
	{
		cmd->args = new;
		free((*token)->word);
		free(*token);
		return (end_new);
	}
	free((*token)->word);
	free(*token);
	ft_free_split(&split);
	return (end_new);
}

void	exeve_checker(t_minishell *minishell, t_cmd *tmp, int *fpip, int *spip)
{
	DIR	*dir;

	dir = opendir(tmp->args_array[0]);
	if ((ft_strlen(tmp->args_array[0]) > 0) && dir
		&& (tmp->args_array[0][0] == '.' || tmp->args_array[0][0] == '/'))
	{
		minishell->exit = 126;
		ft_printf_fd(2, "minishell: %s: is a directory\n",
			tmp->args_array[0]);
		closedir(dir);
		free_child(minishell, minishell->exit);
	}
	if (dir)
		closedir(dir);
	if (!tmp->bin || tmp->bin[0] == '\0')
	{
		minishell->exit = 127;
		close_fds(fpip, spip);
		ft_printf_fd(2, "minishell: %s: command not found\n",
			tmp->args_array[0]);
		free_child(minishell, minishell->exit);
	}
}
