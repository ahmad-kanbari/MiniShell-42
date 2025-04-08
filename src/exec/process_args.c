/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaile <mhaile@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 19:08:23 by akanbari          #+#    #+#             */
/*   Updated: 2024/02/04 16:58:50 by mhaile           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	extend(t_minishell *minishell, t_cmd *cmd, int env, int count_args)
{
	cmd->cmd = handle_quotes(minishell, cmd->cmd, 1);
	if (ft_strlen(cmd->cmd) == 0 && env == 1 && count_args > 0)
	{
		if (ft_strlen(cmd->args->word) && cmd->args->type != T_REDIRECT)
		{
			cmd->cmd = ft_strdup(cmd->args->word);
			cmd->args = remove_redirect(cmd->args, &cmd->args);
			env = 0;
		}
	}
	else if (ft_strlen(cmd->cmd) == 0 && count_args == 0 && env == 1)
		return (-1);
	return (0);
}

int	process_args2(t_minishell *minishell, t_cmd *cmd)
{
	int		env;
	int		count_args;

	env = 0;
	if (cmd->cmd && cmd->cmd[0] == '$')
		env = 1;
	count_args = token_list_size(&cmd->args);
	if (cmd->cmd)
	{
		if (extend(minishell, cmd, env, count_args) == 0)
		{
			if (cmd->bin)
				ft_strdel(&cmd->bin);
			cmd->bin = get_bin(minishell, cmd->cmd);
			if (cmd->args_array)
				ft_free_split(&cmd->args_array);
			cmd->args_array = join_args(minishell, cmd);
		}
		else
			return (-1);
	}
	return (0);
}

int	wild_quotes(t_minishell *minishell, t_token *tmp, int *env)
{
	if (tmp->word && tmp->word[0] == '$')
		*env = 1;
	if (!tmp->prev || !ft_ifstrequal(tmp->prev->word, "<<"))
	{
		tmp->word = handle_quotes(minishell, tmp->word, 1);
		if (!tmp->word)
		{
			if (tmp->next)
				tmp = tmp->next;
			*env = 0;
			return (1);
		}
	}
	return (0);
}

int	process_args(t_minishell *minishell, t_cmd *cmd)
{
	t_token	*tmp;
	int		env;
	int		only_empty_env;

	tmp = cmd->args;
	env = 0;
	while (tmp)
	{
		env = 0;
		if (env == 0)
		{
			if (wild_quotes(minishell, tmp, &env))
				continue ;
		}
		tmp = tmp->next;
	}
	only_empty_env = process_args2(minishell, cmd);
	return (only_empty_env);
}
