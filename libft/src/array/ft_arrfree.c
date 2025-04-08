/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrfree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akanbari <akanbari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 21:25:15 by akanbari          #+#    #+#             */
/*   Updated: 2024/01/01 19:54:02 by akanbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_arrfree(char	**arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
		ft_free(arr[i++]);
	free(arr);
	arr = NULL;
}
