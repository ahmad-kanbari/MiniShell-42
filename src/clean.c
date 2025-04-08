/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaile <mhaile@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 19:00:39 by akanbari          #+#    #+#             */
/*   Updated: 2024/02/02 22:08:27 by mhaile           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_clean(t_minishell *minishell)
{
	if (minishell->cmd_list)
		clear_cmd_list(&minishell->cmd_list, free);
	if (minishell->line_buf)
		ft_strdel(&minishell->line_buf);
	if (minishell->token_list)
		clear_token_list(&minishell->token_list);
	if (minishell->exit_str)
		ft_strdel(&minishell->exit_str);
	if (minishell->env_sorted_list)
		free_env_var_list(&minishell->env_sorted_list);
	if (minishell->exit_str)
		ft_strdel(&minishell->exit_str);
	if (minishell->curdir)
		ft_strdel(&minishell->curdir);
	unlink_file();
}

void	free_child(t_minishell *minishell, int exit_num)
{
	if (minishell->bin)
		ft_free_split(&minishell->bin);
	if (minishell->cmd_list)
		clear_cmd_list(&minishell->cmd_list, free);
	if (minishell->line_buf)
		ft_strdel(&minishell->line_buf);
	if (minishell->env_list)
		free_env_var_list(&minishell->env_list);
	if (minishell->token_list)
		clear_token_list(&minishell->token_list);
	if (minishell->exit_str)
		ft_strdel(&minishell->exit_str);
	if (minishell->exit_str)
		ft_strdel(&minishell->exit_str);
	if (minishell->env_array_local)
		ft_free_split(&minishell->env_array_local);
	close_fds(minishell->fpip, minishell->spip);
	if (minishell->curdir)
		ft_strdel(&minishell->curdir);
	if (minishell->env_sorted_list)
		free_env_var_list(&minishell->env_sorted_list);
	exit(exit_num);
}

void	free_and_exit(t_minishell *minishell, int exit_num)
{
	if (minishell->bin)
		ft_free_split(&minishell->bin);
	if (minishell->cmd_list)
		clear_cmd_list(&minishell->cmd_list, free);
	if (minishell->line_buf)
		ft_strdel(&minishell->line_buf);
	if (minishell->env_list)
		free_env_var_list(&minishell->env_list);
	if (minishell->token_list)
		clear_token_list(&minishell->token_list);
	if (minishell->exit_str)
		ft_strdel(&minishell->exit_str);
	if (minishell->exit_str)
		ft_strdel(&minishell->exit_str);
	if (minishell->env_array_local)
		ft_free_split(&minishell->env_array_local);
	unlink_file();
	if (minishell->curdir)
		ft_strdel(&minishell->curdir);
	if (minishell->env_sorted_list)
		free_env_var_list(&minishell->env_sorted_list);
	rl_clear_history();
	exit(exit_num);
}

void	free_heredoc(t_minishell *minishell, int exit_num)
{
	(void)exit_num;
	if (minishell->bin)
		ft_free_split(&minishell->bin);
	if (minishell->cmd_list)
		clear_cmd_list(&minishell->cmd_list, free);
	if (minishell->line_buf)
		ft_strdel(&minishell->line_buf);
	if (minishell->env_list)
		free_env_var_list(&minishell->env_list);
	if (minishell->token_list)
		clear_token_list(&minishell->token_list);
	if (minishell->exit_str)
		ft_strdel(&minishell->exit_str);
	if (minishell->exit_str)
		ft_strdel(&minishell->exit_str);
	if (minishell->env_array_local)
		ft_free_split(&minishell->env_array_local);
	if (minishell->curdir)
		ft_strdel(&minishell->curdir);
	if (minishell->env_sorted_list)
		free_env_var_list(&minishell->env_sorted_list);
	close_fds(minishell->fpip, minishell->spip);
	exit(exit_num);
}

void	free_panic_exit(t_minishell *minishell, char *error, int exit_status)
{
	if (minishell->bin)
		ft_free_split(&minishell->bin);
	if (minishell->cmd_list)
		clear_cmd_list(&minishell->cmd_list, free);
	if (minishell->line_buf)
		ft_strdel(&minishell->line_buf);
	if (minishell->env_list)
		free_env_var_list(&minishell->env_list);
	if (minishell->token_list)
		clear_token_list(&minishell->token_list);
	if (minishell->exit_str)
		ft_strdel(&minishell->exit_str);
	if (minishell->curdir)
		ft_strdel(&minishell->curdir);
	rl_clear_history();
	perror(error);
	exit(exit_status);
}
