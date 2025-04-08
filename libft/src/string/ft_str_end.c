/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_end.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaile <mhaile@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 23:16:30 by akanbari          #+#    #+#             */
/*   Updated: 2024/02/01 15:43:28 by mhaile           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int	ft_str_end(char *str, char *end)
{
	int		i;
	int		j;

	if (!str)
		return (0);
	i = ft_strlen(str) - 1;
	j = ft_strlen(end) - 1;
	if (i < j)
		return (0);
	while (str[i] && end[j])
	{
		if (str[i] != end[j])
			return (0);
		j--;
		i--;
	}
	return (1);
}
