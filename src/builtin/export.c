/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaile <mhaile@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 19:16:02 by akanbari          #+#    #+#             */
/*   Updated: 2024/02/04 13:10:56 by mhaile           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	free_s1_s2(char **s1, char **s2)
{
	ft_strdel(s1);
	ft_strdel(s2);
}

void	export_cmd_change(t_minishell *minishell, t_token *args,
						char **split, int join)
{
	int		ex;
	char	*s1;
	char	*s2;
	t_env	*newval;

	s1 = NULL;
	s2 = NULL;
	ex = 0;
	if (ft_is_in_stri('=', args->word) == -1)
		ex = 1;
	if (split[0])
		s1 = ft_strdup(split[0]);
	if (split[1])
		s2 = ft_strdup(split[1]);
	if (!(modify_env_list(minishell, split, ex, join)))
	{
		newval = env_new(s1, s2, 0);
		if (ex == 0)
			newval->sign = 1;
		insert_sorted_env_node(&minishell->env_list, newval);
	}
	else
		free_s1_s2(&s1, &s2);
	if (ft_ifstrequal(split[0], "PATH"))
		parse_bin(minishell);
}

void	export_no_args(t_minishell *minishell)
{
	t_env	*tmp;
	char	*key;
	char	*value;

	tmp = minishell->env_list;
	while (tmp)
	{
		if (tmp->key)
			key = ft_strdup(tmp->key);
		else
			key = NULL;
		if (tmp->value)
			value = ft_strdup(tmp->value);
		else
			value = NULL;
		insert_sorted_env_node(&minishell->env_sorted_list, \
			env_new(key, value, tmp->sign));
		tmp = tmp->next;
	}
	env_cmd_export(&minishell->env_sorted_list);
}

void	export_cmd_full(t_minishell *minishell, t_cmd *cmd, char **split,
					t_token *args)
{
	char	*to_free;
	int		join;

	join = 0;
	if (ft_str_end(split[0], "+"))
	{
		to_free = split[0];
		split[0] = ft_strndup(split[0], ft_strlen(split[0]) - 1);
		free(to_free);
		join = 1;
	}
	if (ft_strlen(args->word) > 0 && env_valid_character(split[0]))
		export_cmd_change(minishell, args, split, join);
	else
	{
		ft_printf_fd(2, "%s: %s: `%s': %s\n", "minishell", cmd->cmd,
			args->word, "not a valid identifier");
		minishell->exit = 1;
		minishell->exit = 1;
	}
}

void	export_cmd(t_minishell *minishell, t_cmd *cmd, int forked)
{
	t_token	*args;
	char	**split;

	args = cmd->args;
	minishell->exit = 0;
	minishell->exit = 0;
	if (!args && forked)
	{
		export_no_args(minishell);
		return ;
	}
	while (args)
	{
		split = ft_split_n(args->word, '=', 1);
		export_cmd_full(minishell, cmd, split, args);
		if (split)
			ft_free_split(&split);
		args = args->next;
	}
}
