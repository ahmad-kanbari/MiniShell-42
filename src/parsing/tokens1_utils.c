/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens1_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akanbari <akanbari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 19:06:01 by akanbari          #+#    #+#             */
/*   Updated: 2024/02/02 18:05:44 by akanbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	add_token_list(t_token **begin, t_token *new)
{
	t_token	*tmp;

	if (!new || !begin)
		return ;
	if (*begin)
	{
		tmp = *begin;
		while (tmp->next)
		{
			tmp->next->prev = tmp;
			tmp = tmp->next;
		}
		tmp->next = new;
		new->prev = tmp;
		new->next = NULL;
	}
	else
		*begin = new;
}

int	token_list_size(t_token **begin)
{
	t_token	*tmp;
	int		i;

	i = 0;
	tmp = *begin;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

int	cmd_list_size(t_cmd **begin)
{
	t_cmd	*tmp;
	int		i;

	i = 0;
	tmp = *begin;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

void	clear_token_list(t_token **begin)
{
	t_token	*tmp;
	t_token	*tmp2;

	if (!begin)
		return ;
	tmp = *begin;
	while (tmp)
	{
		ft_strdel(&tmp->word);
		tmp2 = tmp->next;
		free(tmp);
		tmp = tmp2;
	}
	*begin = NULL;
}

//create a token, based on the minishell->count
t_token	*create_token(t_minishell *minishell, int i)
{
	t_token	*new;

	if (!minishell->count)
		return (NULL);
	new = ft_calloc(1, sizeof(t_token));
	if (!(new))
		free_and_exit(minishell, 1);
	new->word = ft_substr(minishell->line_buf, i - minishell->count, \
		minishell->count);
	minishell->count = 0;
	return (new);
}
