/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaile <mhaile@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 21:52:35 by akanbari          #+#    #+#             */
/*   Updated: 2024/02/01 15:48:07 by mhaile           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// int	ft_strncmp(const char *s1, const char *s2, size_t n)
// {
// 	unsigned char	*ss1;
// 	unsigned char	*ss2;

// 	if (n == 0)
// 		return (0);
// 	ss1 = (unsigned char *)s1;
// 	ss2 = (unsigned char *)s2; 
// 	while (n > 0)
// 	{
// 		if (*ss1 != *ss2)
// 			return (*ss1 - *ss2); 
// 		if (*ss1 == '\0' || *ss2 == '\0')
// 			return (0);
// 		ss1++;
// 		ss2++;
// 		n--;
// 	}
// 	return (0);
// }

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int	i;

	i = 0;
	while (n-- && (s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			return ((unsigned char)(s1[i]) - (unsigned char)(s2[i]));
		i++;
	}
	return (0);
}
