/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstswap_cont.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaile <mhaile@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 21:41:50 by akanbari          #+#    #+#             */
/*   Updated: 2024/01/31 22:56:19 by mhaile           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstswap_cont(t_list *lst1, t_list *lst2)
{
	void	*tmp;

	if (!lst1 || !lst2)
		return (0);
	tmp = lst1->content;
	lst1->content = lst2->content;
	lst2->content = tmp;
	return (1);
}
