/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_cmp.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaile <mhaile@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 21:40:17 by akanbari          #+#    #+#             */
/*   Updated: 2024/01/31 22:54:54 by mhaile           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back_cmp(t_list **lst, t_list *new, \
		int (*cmp)(void *, void *))
{
	t_list	*n;

	if (lst == NULL || *lst == NULL)
	{
		ft_lstadd_front(lst, new);
		return ;
	}
	if (cmp((*lst)->content, new->content) < 0)
		ft_lstadd_front(lst, new);
	else if ((*lst)->next == NULL)
		ft_lstadd_back(lst, new);
	else
	{
		n = *lst;
		while (n->next != NULL)
		{
			if (cmp((n->next)->content, new->content) < 0)
				break ;
			n = n->next;
		}
		new->next = n->next;
		n->next = new;
	}
}
