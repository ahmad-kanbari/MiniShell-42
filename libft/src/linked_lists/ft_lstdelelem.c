/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelelem.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaile <mhaile@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 21:32:51 by akanbari          #+#    #+#             */
/*   Updated: 2024/01/31 22:55:43 by mhaile           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelelem(t_list **lst, t_list *elem, void (*del)(void *))
{
	t_list	*tmp;
	t_list	*last;

	if (!lst)
		return ;
	tmp = *lst;
	last = NULL;
	while (tmp)
	{
		if (tmp == elem)
		{
			if (last)
				last->next = tmp->next;
			else
				*lst = tmp->next;
			ft_lstdelone(tmp, del);
			break ;
		}
		last = tmp;
		tmp = tmp->next;
	}
}
