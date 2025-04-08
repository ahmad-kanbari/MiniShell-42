/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaile <mhaile@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 19:15:49 by akanbari          #+#    #+#             */
/*   Updated: 2024/02/01 22:18:25 by mhaile           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	env_cmd(t_minishell *shell, t_env **begin)
{
	t_env	*tmp;

	(void)shell;
	tmp = *begin;
	if (!*begin)
		return ;
	while (tmp)
	{
		if (tmp->value)
			ft_printf("%s=%s\n", tmp->key, tmp->value);
		else if (tmp->sign == 1 && tmp->value == NULL)
			ft_printf("%s=\n", tmp->key);
		tmp = tmp->next;
	}
}
