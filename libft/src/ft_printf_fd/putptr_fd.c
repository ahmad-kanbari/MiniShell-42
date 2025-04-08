/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putptr_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akanbari <akanbari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 11:24:41 by aajaanan          #+#    #+#             */
/*   Updated: 2024/01/03 20:06:30 by akanbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf_fd.h"

void	putptr_fd(int fd, void *ptr, int *counter)
{
	if (ptr == NULL)
		putstr_fd(fd, "0x0", counter);
	else
	{
		putstr_fd(fd, "0x", counter);
		puthex_fd(fd, (t_ullint)ptr, 'x', counter);
	}
}
