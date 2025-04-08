/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putstr_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akanbari <akanbari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 11:22:27 by aajaanan          #+#    #+#             */
/*   Updated: 2023/12/29 03:39:08 by akanbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf_fd.h"

void	putstr_fd(int fd, char *str, int *counter)
{
	if (!str)
		str = "(null)";
	while (*str)
	{
		write(fd, &(*str), 1);
		(*counter)++;
		str++;
	}
}
