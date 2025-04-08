/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   puthex_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akanbari <akanbari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 11:24:12 by aajaanan          #+#    #+#             */
/*   Updated: 2024/01/03 20:02:52 by akanbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf_fd.h"

void	puthex_fd(int fd, t_ullint n, char case_type, int *counter)
{
	char	*hex;

	hex = "0123456789abcdef";
	if (case_type == 'X')
		hex = "0123456789ABCDEF";
	if (n >= 16)
	{
		puthex_fd(fd, n / 16, case_type, counter);
		puthex_fd(fd, n % 16, case_type, counter);
	}
	else
		putchar_fd(fd, hex[n], counter);
}
