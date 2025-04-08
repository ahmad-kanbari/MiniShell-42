/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putunbr_fd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akanbari <akanbari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 14:27:08 by aajaanan          #+#    #+#             */
/*   Updated: 2023/12/29 03:39:10 by akanbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf_fd.h"

void	putunbr_fd(int fd, unsigned int n, int *counter)
{
	if (n >= 10)
	{
		putnbr_fd(fd, n / 10, counter);
		putnbr_fd(fd, n % 10, counter);
	}
	else
		putchar_fd(fd, n + '0', counter);
}
