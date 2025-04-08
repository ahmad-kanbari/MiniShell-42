/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_ascii_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaile <mhaile@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 20:33:36 by akanbari          #+#    #+#             */
/*   Updated: 2024/01/31 22:47:19 by mhaile           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int	is_ascii_str(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (!ft_isascii(str[i]))
			return (0);
		i++;
	}
	return (1);
}
