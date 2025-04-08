/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaile <mhaile@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 18:46:28 by akanbari          #+#    #+#             */
/*   Updated: 2024/01/31 22:55:53 by mhaile           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
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
