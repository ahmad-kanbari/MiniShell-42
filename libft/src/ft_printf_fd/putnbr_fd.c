/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putnbr_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akanbari <akanbari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 11:23:09 by aajaanan          #+#    #+#             */
/*   Updated: 2023/12/29 03:38:51 by akanbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf_fd.h"

void	putnbr_fd(int fd, int n, int *counter)
{
	if (n == -2147483648)
		putstr_fd(fd, "-2147483648", counter);
	else if (n < 0)
	{
		putchar_fd(fd, '-', counter);
		putnbr_fd(fd, -n, counter);
	}
	else if (n >= 10)
	{
		putnbr_fd(fd, n / 10, counter);
		putnbr_fd(fd, n % 10, counter);
	}
	else
		putchar_fd(fd, n + '0', counter);
}
