/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_second_free.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaile <mhaile@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 20:08:22 by mhaile            #+#    #+#             */
/*   Updated: 2024/02/01 15:47:36 by mhaile           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_strjoin_second_free(char const *s1, char const *s2)
{
	char	*str;

	if (!s2)
	{
		str = ft_strdup(s1);
		free((void *)s1);
		return (str);
	}
	str = (char *)ft_calloc(1, sizeof(char)
			* (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	ft_strcpy(str, s1);
	ft_strcat(str, s2);
	free((void *)s2);
	return (str);
}
