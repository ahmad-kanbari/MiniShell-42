/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_unsigned.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akanbari <akanbari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 20:11:26 by akanbari          #+#    #+#             */
/*   Updated: 2023/12/12 20:58:31 by akanbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbr_unsigned_fd(t_uint n, int fd, int *plen)
{
	unsigned int	value;

	if (n > 9)
	{
		ft_putnbr_pfd(n / 10, fd, plen);
	}
	value = n % 10 + '0';
	ft_putchar_pfd(value, fd, plen);
}
