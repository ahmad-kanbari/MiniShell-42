/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaile <mhaile@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 19:16:17 by akanbari          #+#    #+#             */
/*   Updated: 2024/02/04 13:10:56 by mhaile           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_env(t_env *env, char *data)
{
	if (ft_ifstrequal(env->key, data))
		return (0);
	return (1);
}

int	is_valid_env2(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (i == 0 && (ft_isdigit(str[i])))
			return (0);
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static void	remove_env_node(t_env **env_list, char *arg)
{
	t_env	*p;
	t_env	*q;

	p = *env_list;
	q = NULL;
	if (ft_strcmp((*env_list)->key, arg) == 0)
	{
		*env_list = (*env_list)->next;
		free_env_node(&p);
		return ;
	}
	while (p && ft_strcmp(p->key, arg) != 0)
	{
		q = p;
		p = p->next;
	}
	if (p == NULL)
		return ;
	q->next = p->next;
	free_env_node(&p);
}

void	unset_cmd(t_minishell *minishell, t_cmd *cmd)
{
	t_token	*args;

	args = cmd->args;
	minishell->exit = 0;
	minishell->exit = 0;
	while (args)
	{
		if (is_valid_env2(args->word))
		{
			remove_env_node(&minishell->env_list, args->word);
			if (ft_ifstrequal(args->word, "PATH"))
				parse_bin(minishell);
		}
		else
		{
			ft_printf_fd(2, "%s: %s: `%s': %s\n", "minishell", cmd->cmd,
				args->word, "not a valid identifier");
			minishell->exit = 1;
			minishell->exit = 1;
		}
		args = args->next;
	}
}
