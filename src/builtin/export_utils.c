/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaile <mhaile@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 20:08:34 by akanbari          #+#    #+#             */
/*   Updated: 2024/02/01 22:20:56 by mhaile           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//only to modify existing one
static	void	modify_env_list_helper(t_env **tmp, int *join, char **split)
{
	if (split[1] && !join)
		(*tmp)->value = ft_strdup(split[1]);
	else if (!split[1] && !join)
		(*tmp)->value = ft_strdup("");
	else if (split[1] && join)
		(*tmp)->value = ft_strjoin_one_free(\
			(*tmp)->value, split[1]);
}

int	modify_env_list(t_minishell *minishell, char **split, int ex, int join)
{
	t_env	*tmp;
	char	*to_free;

	tmp = minishell->env_list;
	while (tmp)
	{
		if (ft_ifstrequal(tmp->key, split[0]))
		{
			if (ex == 0)
				tmp->sign = 1;
			if (ex != 2)
				tmp->tmp = 0;
			if (ex == 1)
				return (1);
			if (!join)
				to_free = (tmp->value);
			modify_env_list_helper(&tmp, &join, split);
			if (!join)
				free(to_free);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}
