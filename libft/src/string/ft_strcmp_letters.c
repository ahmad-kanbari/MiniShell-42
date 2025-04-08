/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp_letters.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akanbari <akanbari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 21:34:07 by akanbari          #+#    #+#             */
/*   Updated: 2024/01/18 21:49:09 by akanbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int	ft_strcmp_letters(const char *s1, const char *s2)
{
	char	c1;
	char	c2;

	while (*s1 && *s2 && ft_isalpha(*s1) && ft_isalpha(*s2))
	{
		c1 = ft_tolower(*s1);
		c2 = ft_tolower(*s2);
		if (c1 != c2)
			return ((unsigned char)c1 - (unsigned char)c2);
		if (!c1 || !c2)
			break ;
		s1++;
		s2++;
	}
	return (0);
}
