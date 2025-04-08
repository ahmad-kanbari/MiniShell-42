/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaile <mhaile@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 14:34:06 by akanbari          #+#    #+#             */
/*   Updated: 2024/02/01 15:48:27 by mhaile           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	i2;

	i = 0;
	i2 = 0;
	if (needle[i2] == '\0')
		return ((char *)haystack);
	if (len == 0)
		return (NULL);
	while (haystack[i] != '\0' && i < len)
	{
		while (haystack[i + i2] != '\0' && haystack[i + i2] == needle[i2]
			&& (i + i2) < len)
			i2++;
		if (needle[i2] == '\0')
			return ((char *)haystack + i);
		i++;
		i2 = 0;
	}
	return (0);
}
