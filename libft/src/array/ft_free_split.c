/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaile <mhaile@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 22:57:55 by akanbari          #+#    #+#             */
/*   Updated: 2024/01/28 19:54:06 by mhaile           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h" 

void	ft_free_split(char ***split)
{
	int		i;

	i = 0;
	while (*split && (*split)[i])
	{
		ft_strdel(&((*split)[i]));
		i++;
	}
	free(*split);
	*split = NULL;
}
