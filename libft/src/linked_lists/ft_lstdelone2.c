/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akanbari <akanbari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 20:54:54 by akanbari          #+#    #+#             */
/*   Updated: 2023/12/07 15:57:41 by akanbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone2(t_list **lst, void (*del)(void **))
{
	if (!lst || !del || !(*lst))
		return ;
	del(&((*lst)->content));
	free(lst);
	(*lst) = NULL;
}
