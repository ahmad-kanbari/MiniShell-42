/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelpos.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akanbari <akanbari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 07:44:39 by akanbari          #+#    #+#             */
/*   Updated: 2023/12/12 21:21:17 by akanbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

static	void	ft_lstdelpos_helper(int position, t_list **prev, \
		t_list **current);

void	ft_lstdelpos(t_list **head, int position)
{
	t_list	*current;
	t_list	*prev;

	current = NULL;
	head = &current;
	prev = *head;
	if (*head == NULL)
		ft_printf("List is already empty");
	else if (position == 1)
	{
		*head = current->next;
		free(current);
		current = NULL;
	}
	else
		ft_lstdelpos_helper(position, &prev, &current);
}

static void	ft_lstdelpos_helper(int position, t_list **prev, t_list **current)
{
	while (position != 1)
	{
		*prev = *current;
		*current = (*current)->next;
		position--;
	}
	(*prev)->next = (*current)->next;
	free(current);
	*current = NULL;
}
