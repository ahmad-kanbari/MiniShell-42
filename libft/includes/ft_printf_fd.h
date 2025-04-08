/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akanbari <akanbari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 03:36:33 by akanbari          #+#    #+#             */
/*   Updated: 2024/01/03 20:02:42 by akanbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_FD_H
# define FT_PRINTF_FD_H

# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <ctype.h>
# include <stdlib.h>
# include <limits.h>
# include <stdarg.h>

typedef unsigned long long int	t_ullint;

void							putchar_fd(int fd, char c, int *counter);
void							puthex_fd(int fd, t_ullint n, char case_type,
									int *counter);
void							putnbr_fd(int fd, int n, int *counter);
void							putptr_fd(int fd, void *ptr, int *counter);
void							putstr_fd(int fd, char *str, int *counter);
void							putunbr_fd(int fd, unsigned int n,
									int *counter);
void							handle_format_specifier_fd(int fd, va_list args,
									char c, int *counter);
int								ft_printf_fd(int fd, const char *format, ...);

#endif