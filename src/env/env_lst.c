/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaile <mhaile@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 22:34:00 by akanbari          #+#    #+#             */
/*   Updated: 2024/02/01 22:28:41 by mhaile           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_env_lstadd_back(t_env **lst, t_env *new)
{
	if (!new)
		return ;
	if (!(*lst))
		*lst = new;
	else
		(ft_env_lstlast(*lst))->next = new;
}

t_env	*ft_env_lstlast(t_env *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

int	ft_env_lstsize(t_env *lst)
{
	int	n_count;

	n_count = 0;
	if (lst == NULL)
		return (0);
	while (lst != NULL)
	{
		n_count++;
		lst = lst->next;
	}
	return (n_count);
}

void	env_cmd_export(t_env **begin)
{
	t_env	*tmp;

	tmp = *begin;
	if (!(*begin))
		return ;
	while (tmp)
	{
		if (!ft_ifstrequal(tmp->key, "_"))
		{
			if (tmp->value
				&& !(tmp->tmp))
				ft_printf_fd(1, "declare -x %s=\"%s\"\n",
					tmp->key, tmp->value);
			else if (tmp->sign == 1 && tmp->value == NULL)
				ft_printf_fd(1, "declare -x %s=\"\"\n", tmp->key);
			else if (!(tmp->value)
				&& !(tmp->tmp))
				ft_printf_fd(1, "declare -x %s\n", tmp->key);
		}
		tmp = tmp->next;
	}
}

int	env_valid_character(char *str)
{
	int		i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (i == 0 && ft_isdigit(str[i]))
			return (0);
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}
