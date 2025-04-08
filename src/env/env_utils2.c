/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaile <mhaile@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 07:41:17 by akanbari          #+#    #+#             */
/*   Updated: 2024/02/01 22:27:58 by mhaile           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**env_to_array(t_minishell *minishell)
{
	int		i;
	t_env	*tmp;
	char	**array;

	array = ft_calloc(1, sizeof (char *) * \
		(ft_env_lstsize(minishell->env_list) + 1));
	if (!array)
		free_and_exit(minishell, 1);
	i = 0;
	tmp = minishell->env_list;
	while (tmp)
	{
		array[i] = ft_strjoin(tmp->key, "=");
		array[i] = ft_strjoin_one_free(array[i], tmp->value);
		i++;
		tmp = tmp->next;
	}
	array[i] = NULL;
	if (minishell->env_array_local)
		ft_free_split(&minishell->env_array_local);
	return (array);
}

int	is_valid_env(char *str)
{
	int		i;
	int		eq_count;

	i = 0;
	eq_count = 0;
	while (str[i])
	{
		if (i == 0 && (ft_isdigit(str[i]) || str[i] == '='))
			return (0);
		if (!ft_isalnum(str[i]) && str[i] != '_' && str[i] != '='
			&& str[i] != '+' && str[i] != '\'' && str[i] != '\"')
			return (0);
		if ((str[i] == '\'' || str[i] == '\"') && eq_count < 1)
			return (0);
		if (eq_count == 0 && str[i] == '+' && str[i + 1] != '=')
			return (0);
		if (str[i] == '=')
			eq_count++;
		i++;
	}
	if (eq_count)
		return (1);
	return (0);
}
