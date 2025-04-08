/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_comands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akanbari <akanbari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 20:32:09 by akanbari          #+#    #+#             */
/*   Updated: 2024/02/03 16:49:19 by akanbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	start_parse(t_minishell *minishell, char *str)
{
	char		*token;
	t_token		*tmp;

	if (!is_ascii_str(str))
	{
		ft_printf_fd(2, "minishell: invalid ascii \
			characters found in string\n");
		return ;
	}
	minishell->line_buf = str;
	split_tokens(minishell, str);
	token = iter_tokens(minishell);
	if (token)
	{
		ft_printf_fd(2, "minishell: syntax error near unexpected token `%s'\n", \
				token);
		return ;
	}
	tmp = minishell->token_list;
	while (tmp)
		parse_tokens(minishell, &tmp);
}

int	parse_tokens2_helper(t_minishell *shell, t_token **tmp, t_cmd *cmd)
{
	(void)shell;
	if ((*tmp)->type == T_PIPE)
	{
		cmd->type = T_PIPE;
		*tmp = (*tmp)->next;
		return (0);
	}
	if ((*tmp)->type == T_SEP)
	{
		cmd->type = T_SEP;
		*tmp = (*tmp)->next;
		return (0);
	}
	return (0);
}

//here you can adjust it to check if it is a file after a rediret 
//and where you are adding if the variable is ENV
int	parse_tokens2(t_minishell *shell, t_token **tmp, t_cmd *cmd)
{
	if ((*tmp)->type == T_WORD && (cmd->cmd || ((*tmp)->prev \
		&& (*tmp)->prev->type == T_REDIRECT)))
		add_token_list(&cmd->args,
			create_arg_token(shell, (*tmp)->word, (*tmp)->type));
	if ((*tmp)->type == T_WORD && !cmd->cmd && (((*tmp)->prev \
		&& (*tmp)->prev->type != T_REDIRECT) || !(*tmp)->prev))
	{
		if (cmd->cmd)
			ft_strdel(&cmd->cmd);
		cmd->cmd = ft_strdup((*tmp)->word);
	}
	if ((*tmp)->type == T_REDIRECT)
		add_token_list(&cmd->args,
			create_arg_token(shell, (*tmp)->word, (*tmp)->type));
	if ((*tmp)->type == T_PIPE)
		return (parse_tokens2_helper(shell, tmp, cmd));
	if ((*tmp)->type == T_SEP)
		return (parse_tokens2_helper(shell, tmp, cmd));
	return (1);
}

void	parse_tokens(t_minishell *minishell, t_token **tmp)
{
	t_cmd	*cmd;

	if ((*tmp)->type == T_NEWLINE)
	{
		*tmp = (*tmp)->next;
		return ;
	}
	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return ;
	while (*tmp)
	{
		if (!parse_tokens2(minishell, tmp, cmd))
			break ;
		if ((*tmp)->type == T_ENV && cmd->cmd)
			add_token_list(&cmd->args,
				create_arg_token(minishell, (*tmp)->word, (*tmp)->type));
		*tmp = (*tmp)->next;
	}
	cmd->bin = get_bin(minishell, cmd->cmd);
	cmd->args_array = join_args(minishell, cmd);
	add_cmd_list(minishell, &minishell->cmd_list, cmd);
}
